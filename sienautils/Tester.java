import siena.*;

public class Tester {

	public static ThinClient siena;

	public static void publishC_getRoom(String method, String args) {
		Notification e = new Notification();

		e.putAttribute("from_component", "client");
		e.putAttribute("data", args);
		e.putAttribute("auth", "true");
		e.putAttribute("username", "denis");
		e.putAttribute("password", "denis");
		e.putAttribute("prot", "HTTP");
		e.putAttribute("address", "http://www.google.com/");
		e.putAttribute("access", "");
		e.putAttribute("chime_method", method);

		System.out.println("publishing " + e.toString());
		try {
			siena.publish(e);
		} catch (SienaException ex) {
			System.err.println("Siena error:" + ex.toString());
		}
   }


    public static void main(String[] args) {
		try {
		    if (args.length != 3) {
				System.err.println("Usage:java Tester [server-uri] [method] [args]");
				System.exit(1);
			}

	    	siena = new ThinClient(args[0]);

	    	//this is the call
	    	publishC_getRoom(args[1], args[2]);

	    	System.out.println("shutting down.");
	   		siena.shutdown();
	    	//Thread.sleep(1000);
	    	//System.exit(0);
		} catch (Exception ex) {
	    	ex.printStackTrace();
	    	System.exit(1);
		}
	}
}
