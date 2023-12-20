package esiot.module_lab_3_2;

public interface CommChannel {
	
	void sendMsg(String msg);
	
	String receiveMsg() throws InterruptedException;

	boolean isMsgAvailable();

}
