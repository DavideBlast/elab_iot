package esiot.module_lab_3_2;

public class MonitoringAgent extends Thread {

	SerialCommChannel channel;
	GreenhouseView view;
	LogView logger;
	
	static final String GR_PREFIX 	=  "gr:";
	static final String LOG_PREFIX 	=  "lo:";
	static final String MSG_IDLE 		= "id";
	static final String MSG_CHECK 		= "ch";
	static final String MSG_COOLING 		= "co";
	static final String MSG_WATERING 		= "wa";
	
	public MonitoringAgent(SerialCommChannel channel, GreenhouseView view, LogView log) throws Exception {
		this.view = view;
		this.logger = log;
		this.channel = channel;
	}
	
	public void run(){
		while (true){
			try {
				String msg = channel.receiveMsg();
				if (msg.startsWith(GR_PREFIX)){
					String cmd = msg.substring(GR_PREFIX.length()); 
					logger.log("new command: "+cmd);				
					if (cmd.startsWith(MSG_IDLE)){
						view.setState("Idle");
					} else if (cmd.startsWith(MSG_CHECK)){
						view.setState("Checking");
					} else if (cmd.startsWith(MSG_WATERING)){
						view.setState("Watering");
						view.setPumpState(true);
					} else if (cmd.startsWith(MSG_COOLING)) {
						view.setState("Cooling");
						view.setFanState(true);
					}
				} else if (msg.startsWith(LOG_PREFIX)){
					this.logger.log(msg.substring(LOG_PREFIX.length()));
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}

}
