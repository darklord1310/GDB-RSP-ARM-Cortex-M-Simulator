import java.awt.*;
import java.util.StringTokenizer;
import javax.swing.JOptionPane;

// contributed by Edward Calver

class Multiplexer2To1Elm extends ChipElm
{
        TestJNI jni;
	boolean hasReset() {return false;}
	public Multiplexer2To1Elm(int xx, int yy) { super(xx, yy); }
	public Multiplexer2To1Elm(int xa, int ya, int xb, int yb, int f, StringTokenizer st)
  {
	    super(xa, ya, xb, yb, f, st);
	}
	String getChipName() { return "Multiplexer2To1"; }

	void setupPins()
  {
	    sizeX = 3;
	    sizeY = 3;
	    pins = new Pin[getPostCount()];

	    pins[0] = new Pin(0, SIDE_W, "I0");
	    pins[1] = new Pin(1, SIDE_W, "I1");
		
	    pins[2] = new Pin(1, SIDE_S, "S0");

	    pins[3] = new Pin(0, SIDE_E, "Q");
	    pins[3].output=true;

	}
	int getPostCount() { return 4; }
	int getVoltageSourceCount() {return 1;}

	void execute()
        {
         int selectedvalue=0;
	 if(pins[2].value) selectedvalue++;
	 pins[3].value=pins[selectedvalue].value;
         
         try {
             jni = new TestJNI();
             System.out.println("In Java, the average is " + jni.average(3, 2));
             //JOptionPane msgBox = new JOptionPane();
             //msgBox.showMessageDialog(null, "In Java, the average is " + jni.average(3, 2), "Result", JOptionPane.INFORMATION_MESSAGE);
         }
         catch(Throwable ex)
         {
             System.out.println(ex.getMessage());
         }
	}
	int getDumpType() { return 184; }
}
