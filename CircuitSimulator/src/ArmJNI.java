/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Jackson's Asus
 */
public class ArmJNI {
    static {
      try {
          System.load("C:/Users/Asus/Desktop/TDD/Project/GDB-RSP-ARM-Cortex-M-Simulator/build/release/dll/gdbserver.dll");
      }
      catch(Throwable ex)
      {
          System.out.println(ex.getMessage());
      }
   }
   
   public native int gdbserver(double period);
}
