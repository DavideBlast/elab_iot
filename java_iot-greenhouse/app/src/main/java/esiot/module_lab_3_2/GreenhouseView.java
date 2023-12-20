package esiot.module_lab_3_2;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;


public class GreenhouseView extends JFrame implements ActionListener {
    
	private JTextField stateInfo;
	private JTextField pumpState;
	private JTextField fanState;
	//private JTextField numItems;
	//private JTextField numSelfTests;
	private Controller controller;	

    public GreenhouseView() {
        super("Smart Greenhouse");
        setSize(600, 120);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		mainPanel.add(Box.createRigidArea(new Dimension(0,20)));

		JPanel infoLine = new JPanel();
		infoLine.setLayout(new BoxLayout(infoLine, BoxLayout.LINE_AXIS));

		stateInfo = new JTextField("--");
		stateInfo.setEditable(false);
		stateInfo.setPreferredSize(new Dimension(200,15));
		infoLine.add(new JLabel("State:"));
		infoLine.add(stateInfo);

		pumpState = new JTextField("--");
		pumpState.setEditable(false);
		pumpState.setPreferredSize(new Dimension(200,15));
		infoLine.add(new JLabel("Pump state:"));
		infoLine.add(pumpState);

		fanState = new JTextField("--");
		fanState.setEditable(false);
		fanState.setPreferredSize(new Dimension(200,15));
		infoLine.add(new JLabel("Fan state:"));
		infoLine.add(fanState);
		
		mainPanel.add(infoLine);
		mainPanel.add(Box.createRigidArea(new Dimension(0,20)));
/* 
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));	    
		refill = new JButton("Refill");
		refill.setEnabled(false);
		buttonPanel.add(refill);
		recover = new JButton("Recover");
		recover.setEnabled(false);
		buttonPanel.add(recover);
		refill.addActionListener(this);
		recover.addActionListener(this);
		mainPanel.add(buttonPanel);
*/
		this.getContentPane().add(mainPanel);

		addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent ev){
				System.exit(-1);
			}
		});
    }

    @Override
    public void actionPerformed(ActionEvent ev) {
        try {
            if (ev.getActionCommand().equals("Refill")){
                //controller.sendMsg("re");
            } else {
                //controller.sendMsg("rc");
            }
        } catch (Exception ex){
            ex.printStackTrace();
        }
    }

    public void registerController(Controller contr){
		this.controller = contr;
	}

    public void setPumpState(boolean msg){
		SwingUtilities.invokeLater(() -> {
			pumpState.setText(msg ? "ON" : "OFF");
		});
	}

	public void setFanState(boolean msg){
		SwingUtilities.invokeLater(() -> {
			fanState.setText(msg ? "ON" : "OFF");
		});
	}

	public void setState(String msg){
		SwingUtilities.invokeLater(() -> {
			pumpState.setText("OFF");
			fanState.setText("OFF");
			stateInfo.setText(msg);
		});
	}

}
