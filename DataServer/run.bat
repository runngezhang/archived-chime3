@del DB.*
@SET JARROOT=C:\pslroot\jars
@javac -classpath .;%JARROOT%\hsql.jar;%JARROOT%\siena-1.1.1-jvm1.3.jar;%JARROOT%\jdom.jar;%JARROOT%\xerces.jar;%JARROOT%\collections.jar xescii\Xescii.java
@java -classpath .;%JARROOT%\hsql.jar;%JARROOT%\siena-1.1.1-jvm1.3.jar;%JARROOT%\jdom.jar;%JARROOT%\xerces.jar;%JARROOT%\collections.jar xescii.Xescii "DB" "senp://localhost:1111" "FRAX"