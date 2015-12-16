import java.awt.*;
import java.util.StringTokenizer;
import javax.swing.JOptionPane;

/**
 *
 * @author Jackson's Asus
 */
public class ARMSim extends ChipElm{
        ArmJNI jni;
	boolean hasReset() {return false;}
	public ARMSim(int xx, int yy) { super(xx, yy); }
	public ARMSim(int xa, int ya, int xb, int yb, int f, StringTokenizer st)
  {
	    super(xa, ya, xb, yb, f, st);
	}
	String getChipName() { return "ARM Simulator"; }

	void setupPins()
  {
	    sizeX = 3;
	    sizeY = 3;
	    pins = new ChipElm.Pin[getPostCount()];

	    pins[0] = new ChipElm.Pin(0, SIDE_W, "P1");

	    pins[0].output=true;

	}
	int getPostCount() { return 1; }
	int getVoltageSourceCount() {return 1;}

	void execute()
        {
         try {
             jni = new ArmJNI();
             int result;
             result = jni.gdbserver(12.55);
             
             if(result == 1)
                 pins[0].value = true;
         }
         catch(Throwable ex)
         {
             System.out.println("Error: " + ex.getMessage());
         }
	}
	int getDumpType() { return 184; }
}
