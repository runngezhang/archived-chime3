 /*    
 * Copyright (c) 2001: The Trustees of Columbia University 
 *    in the City of New York.  All Rights Reserved.
 *
 */

package psl.chime.frax.protocols.http;
import psl.chime.frax.protocols.FRAXProtocol;
import HTTPClient.*;
import java.net.*;
import java.io.*;
import psl.chime.frax.plugs.PlugStarter;



public class HTTPProtocol extends FRAXProtocol  {

    public static final String PROTOCOL_NAME = "HTTP"; 
    public String URLString = "";
    private String final_str;
    private DataInputStream returned; 
    HTTPResponse rsp;
    URL dest;
    public String metaData;
   
    /**
     * a general purpose consrtuctor to store an internal
     * representation of the data so we can be ready
     * when processObject is called
     */
    public HTTPProtocol(String object) {
	this.URLString = object;
    }

    /**
     * makes a url object - for internal use only
     */
    private URL makeURLObj(String object) {
	try {
	    dest = new URL(object);
	} catch (Exception e) {
	    dest = null;
	}
	return dest;
    }
    

    /**
     * returns an HTTPResponse object associated with the 
     * object that the user wishes to retrieve
     */
    private HTTPResponse getStream(String object) {

	try {
	    URL dest = makeURLObj(object);
	    
	    if (dest == null)
		return null;
	    
	    HTTPConnection con = new HTTPConnection(dest);
	    con.setAllowUserInteraction(true);
	    rsp = con.Get(dest.getPath());
	    
	    if (rsp.getStatusCode() >= 300 && rsp.getStatusCode() < 400) {
		System.err.println("Received Error: "+rsp.getReasonLine());
		System.err.println(new String(rsp.getData()));
		return null;
	    } else {
		returned = new DataInputStream(rsp.getInputStream());
		return rsp;
	    }
	    
	} catch (IOException ioe) {
	    System.err.println(ioe.toString());
	    return null;
	}
	catch (ModuleException me) {
	    System.err.println("Error handling request: " + me.getMessage());
	    return null;
	}
    }


    /**
     * Helper method to see if maybe this object can be
     * resolved as an HTTP directory
     */
    private String makeDir(String url) {
	url = url.trim();

	if (url.endsWith("/"))
	    return null;

	else
	    return url + "/";
    }
	    

    /**
     * Attach index.html and see if we can resolve it
     */
    private String addIndexHtml(String url) {
	url = url.trim();

	if (url.endsWith("/"))
	    return url + "index.html";
	else
	    return url + "/index.html";
    }
		

    /**
     * The method which is called to get the object and 
     * call the appropriate plug
     */
    public boolean processObject() {
	boolean isDir = false;
	HTTPResponse rsp;

	//try the URL as specified
	rsp = getStream(URLString);
	
	if (rsp == null) 
	    //try to attach index.html
	    getStream(addIndexHtml(URLString));
	
	
	if (rsp == null) {
	    //try to get it as a directory
	    String mydir = makeDir(URLString);
	    if(mydir != null) {
		rsp = getStream(makeDir(URLString));
		isDir = true;
	    }
	}
	
	
	//give up - no idea what this is
	if (rsp == null)
	    return false;
	
	else {
	   
	    metaData = generateMetaData(rsp);
	  

	    try {
		String returning = rsp.getEffectiveURI().toString();

		if (!isDir && returning.endsWith("/"))
		    goPlug(PROTOCOL_NAME, returning + "index.html", createParams());
		else 
		    goPlug(PROTOCOL_NAME, returning, createParams());
		return true;

		//maybe the getEffective URI method will fail so have a backup
	    } catch (Exception e) {

		String returning = rsp.getOriginalURI().toString();

		if (!isDir && returning.endsWith("/"))
		    goPlug(PROTOCOL_NAME, returning + "index.html", createParams());
		else 
		    goPlug(PROTOCOL_NAME, returning, createParams());
	
		return true;
	    }
	}
	
    }
	   
    /**
     * This was written before FRAXProtocol so this method
     * is included but can be replaced with the generic one 
     * from FRAXProtocol since we are extending it
     */
    private Object[] createParams() {
	Object[] const_param = new Object[3];
	const_param[0] = metaData;
	System.out.println("*********The metaData is: " + metaData);
	
	const_param[1] = returned;

	try {
	    const_param[2] = new Long(getField(rsp, "Content-Length"));
	} catch (NumberFormatException e) {
	    System.err.println("The length can't be cast");
	    const_param[2] = new Long(-1);
	    return const_param;
	}
	return const_param;
    }
    
    /**
     * returns a field which the user
     * has requested from the HTTPResponse which we got
     */
    private String getField(HTTPResponse rsp, String name) {
	try {
	    return rsp.getHeader(name);
	} catch (Exception e) {
	    return "";
	}
    }
    

    /** 
     * generates the XML stuff from the metadata that this protocol
     * has been able to acquire
     */
    private String generateMetaData(HTTPResponse rsp) {
	String temp = "<Protocol>" + PROTOCOL_NAME + "</Protocol>\n";
	try {
	    temp = temp + "<Name>" + rsp.getEffectiveURI().toString() + "</Name>\n";
	} catch (Exception e) {
	    System.err.println("can't get URL");
	}
	
	temp = temp + "<Size>" + getField(rsp, "Content-Length") + "</Size>\n";
	temp = temp + "<Expiration>" + getField(rsp, "Expires") + "</Expiration>\n";
	temp = temp + "<Delivered>" + getField(rsp, "Date") + "</Delivered>\n";
	temp = temp + "<Type>" + getField(rsp, "Content-Type") + "</Type>\n";
	temp = temp + "<Last-Modified>" + getField(rsp, "Last-Modified") + "</Last-Modified>\n";

	return temp;
	
    }
    
    /** 
     * testing routine
     */
    public static void main (String [] args) {
	//HTTPProtocol hp = new HTTPProtocol("http://www.columbia.edu/~daa82/");
	HTTPProtocol hp = new HTTPProtocol("http://www.nytimes.com/index.html");
	hp.processObject();
    }
}
	    