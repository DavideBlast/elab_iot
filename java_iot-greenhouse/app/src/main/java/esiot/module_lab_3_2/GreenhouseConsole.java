package esiot.module_lab_3_2;

import javax.swing.SwingUtilities;

public class GreenhouseConsole {

	static GreenhouseView view = null;
	static LogView log = null;

	public static void main(String[] args) throws Exception {
		SwingUtilities.invokeAndWait(() -> {
			view = new GreenhouseView();
			log = new LogView();
		});

		String portName = "COM3";
		Controller contr = new Controller(portName,view,log);
		view.registerController(contr);
		SwingUtilities.invokeLater(() -> {
			view.setVisible(true);
			log.setVisible(true);
		});
	}
}