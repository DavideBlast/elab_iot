package esiot.module_lab_3_2;

public class Controller {
    
    SerialCommChannel channel;
    GreenhouseView view;

    public Controller(String port, GreenhouseView view, LogView log) throws Exception {
        this.view = view;
        this.channel = new SerialCommChannel(port, 115200);
		new MonitoringAgent(channel,view,log).start();

		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		
    }
}
