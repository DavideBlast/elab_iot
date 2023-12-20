package esiot.module_lab_3_2;

public class TestRemoteBlinking {

	public static void main(String[] args) throws Exception {
		SerialCommChannel channel = new SerialCommChannel("COM3",115200);		
		// SerialCommChannel channel = new SerialCommChannel("/dev/cu.usbmodem1411",9600);		
		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		

		
		while (true){
			channel.sendMsg("100.2,35.5");
			String msg = channel.receiveMsg();
			System.out.println(msg);
			Thread.sleep(1000);

			channel.sendMsg("45.2,20.3");
			msg = channel.receiveMsg();
			System.out.println(msg);		
			Thread.sleep(1000);

			channel.sendMsg("100.4,24.5");
			msg = channel.receiveMsg();
			System.out.println(msg);
			Thread.sleep(1000);
		}
	}

}
