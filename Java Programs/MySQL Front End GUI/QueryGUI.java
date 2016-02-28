/*
 * Joseph Johnson IV
 * Course: CNT 4714 - Enterprise Programming Spring 2016
 * Assignment title: Two-Tier Client-Server Application Development With MySQL and JDBC
 * Program to create a front-end GUI to allow a user to log into a MySQL database and run queries
 */

import java.sql.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class QueryGUI extends JFrame
{
	private static final long serialVersionUID = 1L;

	// Declaring all of the GUI components I will be using
	private String defaultDriver, defaultUrl;
	private JLabel enterDBInfo, enterSQL, chooseDriver, chooseDb, enterUser, enterPass;
	private JLabel connectionStatus, resultL;

	private static final JComboBox<String> chooseDriverCB = new JComboBox<String>();
	private static final JComboBox<String> chooseDbCB = new JComboBox<String>();

	private JTextArea enterSQLTF;
	private JTextField enterUserTF;
	private JPasswordField enterPassTF;

	private JButton connectBTN, clearBTN, executeBTN, clearResultBTN;

	private connectBTNListener cbListener;
	private clearBTNListener clbListener;
	private executeBTNListener ebListener;
	private clearResultBTNListener clrbListener;

	private JScrollPane results;

	private ResultSetTableModel tableModel;

	private static QueryGUI a;

	// Constructor for the GUI
	public QueryGUI()
	{
		setTitle("SQL Client GUI - (JJIV)");
		setSize(900,500);

		// Initializing the variables previously declared
		defaultDriver = "com.mysql.jdbc.Driver";
		defaultUrl = "jdbc:mysql://localhost:3306/project3";
		enterDBInfo = new JLabel("Enter Database Information");
		enterSQL = new JLabel("Enter a SQL Command");
		chooseDriver = new JLabel("JDBC Driver");
		chooseDb = new JLabel("Database URL");
		enterUser = new JLabel("Username");
		enterPass = new JLabel("Password");

		connectionStatus = new JLabel("No Connection Now");
		resultL = new JLabel ("SQL Execution Result");

		enterUserTF = new JTextField(20);
		enterPassTF = new JPasswordField(20);
		enterSQLTF = new JTextArea();
		new JTextField(20);

		connectBTN = new JButton("Connect to Database");
		clearBTN = new JButton("Clear Command");
		clearResultBTN = new JButton("Clear Result Window");
		executeBTN = new JButton("Execute SQL Command");

		cbListener = new connectBTNListener();
		clbListener = new clearBTNListener();
		ebListener = new executeBTNListener();
		clrbListener = new clearResultBTNListener();

		results = new JScrollPane();

		// For simplicity, using absolute positioning for the GUI elements
		Container pane = getContentPane();
		pane.setLayout(null);

		enterDBInfo.setBounds(10, 0, 200, 20);
		enterSQL.setBounds(450, 0, 200, 20);
		chooseDriver.setBounds(10, 21, 70 , 20);
		chooseDriverCB.setBounds(100, 21, 300, 20);
		chooseDb.setBounds(10, 41, 80, 20);
		chooseDbCB.setBounds(100, 41, 300, 20);
		enterUser.setBounds(10, 61, 60, 20);
		enterUserTF.setBounds(100, 61, 301, 20);
		enterPass.setBounds(10, 81, 60, 20);
		enterPassTF.setBounds(100, 81, 301, 20);
		enterSQLTF.setBounds(450, 21, 400, 100);

		connectionStatus.setBounds(10, 150, 300, 20);
		connectBTN.setBounds(300, 150, 170, 20);
		clearBTN.setBounds(490, 150, 170, 20);
		executeBTN.setBounds(680, 150, 170, 20);
		resultL.setBounds(10, 180, 200, 20);
		results.setBounds(10, 205, 840, 200);

		clearResultBTN.setBounds(10, 410, 170, 20);
		connectBTN.addActionListener(cbListener);
		clearBTN.addActionListener(clbListener);
		executeBTN.addActionListener(ebListener);
		clearResultBTN.addActionListener(clrbListener);

		pane.add(enterDBInfo);
		pane.add(enterSQL);
		pane.add(chooseDriver);
		pane.add(chooseDriverCB);
		pane.add(chooseDb);
		pane.add(chooseDbCB);
		pane.add(enterUser);
		pane.add(enterUserTF);
		pane.add(enterPass);
		pane.add(enterPassTF);
		pane.add(enterSQLTF);
		pane.add(connectionStatus);
		pane.add(connectBTN);
		pane.add(clearBTN);
		pane.add(executeBTN);
		pane.add(resultL);
		pane.add(results);
		pane.add(clearResultBTN);

		enterSQLTF.setLineWrap(true);
		chooseDriverCB.addItem(defaultDriver);
		chooseDbCB.addItem(defaultUrl);
		connectionStatus.setForeground(Color.RED);
		connectBTN.setBackground(Color.BLUE);
		connectBTN.setForeground(Color.WHITE);
		executeBTN.setBackground(Color.GREEN);
		executeBTN.setEnabled(false);
		clearResultBTN.setBackground(Color.YELLOW);
		results.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
		results.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);

		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}

	// ActionListener for the Connect To Database Button
	public class connectBTNListener implements ActionListener
	{
		@Override
		public void actionPerformed(ActionEvent arg0)
		{
			try
			{
				// Create a Result Table from the provided class
				tableModel = new ResultSetTableModel(chooseDriverCB.getSelectedItem().toString(),
						chooseDbCB.getSelectedItem().toString(), enterUserTF.getText(), enterPassTF.getText(), "");
			}

			// Show error message in a pop up if there is an exception
			catch (Exception ex)
			{ JOptionPane.showMessageDialog(a, ex.toString().split(": ")[1]); }

			connectionStatus.setText("Connected to " + chooseDbCB.getSelectedItem().toString());
			connectBTN.setEnabled(false);
			executeBTN.setEnabled(true);
		}
	}

	// Listener for the Clear Command Button
	public class clearBTNListener implements ActionListener
	{
		@Override // Just setting the text for the command box to the empty string
		public void actionPerformed(ActionEvent e) { enterSQLTF.setText(""); }

	}

	// Listener for the Execute Command Button
	public class executeBTNListener implements ActionListener
	{
		@Override
		public void actionPerformed(ActionEvent e) {

			// MySQL gives a lot of casing options for commands so I will lowercase it for easier comparison
			String query = enterSQLTF.getText().toLowerCase();

			// Select is the only Query possible that is not an update
			if (query.startsWith("select"))
			{
				try
				{
					// Using the user input rather thant he manipulated input
					tableModel.setQuery(enterSQLTF.getText());

					// Removing the old scrollpane
					a.remove(results);

					// Creating new scrollpane that holds the results table and adding it
					results = new JScrollPane(new JTable(tableModel));
					results.setBounds(10, 205, 840, 200);
					a.add(results);
				}
				catch (SQLException ex)
				{ JOptionPane.showMessageDialog(a, ex.toString().split(": ")[1]); }

			}

			// If we make it here, then the command is an update query, use .setUpdate instead of .setQuery
			else
			{
				try
				{
					tableModel.setUpdate(enterSQLTF.getText());
					a.remove(results);

					results = new JScrollPane(new JTable(tableModel));
					results.setBounds(10, 205, 840, 200);
					a.add(results);
				}
				catch (SQLException ex)
				{ JOptionPane.showMessageDialog(a, ex.toString().split(": ")[1]); }

			}

		}
	}

	// Listener for the Clear Result Window Button
	public class clearResultBTNListener implements ActionListener
	{

		@Override // Remove the old scrollpane and replace it with a blank one
		public void actionPerformed(ActionEvent arg0)
		{
			a.remove(results);

			results = new JScrollPane(new JTable());
			results.setBounds(10, 205, 840, 200);
			a.add(results);

		}
	}

	public static void main (String args[])
	{	a =  new QueryGUI(); }
}
