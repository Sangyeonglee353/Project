/*package LearningPlanner;

import javax.swing.*;
import java.awt.*;

public class CheckStudyPlan extends JFrame {
	private String [] fruits = {"2021-11-14 �Ͽ���", "2021-11-15 ������", "2021-11-16 ȭ����"}; 
	
	public CheckStudyPlan() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setContentPane(new MyPanel());
		
		Container c = getContentPane();
		c.setLayout(null);

		JComboBox<String> combo = new JComboBox<String>(fruits);
		c.add(combo);
		combo.setBounds(145, 105, 130, 30);
		
		JLabel b1 = new JLabel("��ǥ�ð�"); // ��ư ����
		b1.setFont(new Font("���� ���", Font.BOLD, 25));
		b1.setLocation(100, 210); // ��ư�� ��ġ ����
		c.add(b1);
		JTextField b2 = new JTextField(20);
		b1.setLocation(100, 210);
		c.add(b2);
		
		b1.setBounds(60, 140, 100, 100);
		b2.setBounds(220, 170, 150, 45);
		
		JLabel b3 = new JLabel("�н� �ܾ"); // ��ư ����
		b3.setFont(new Font("���� ���", Font.BOLD, 25));
		b3.setLocation(100, 210); // ��ư�� ��ġ ����
		c.add(b3);
		JTextField b4 = new JTextField(20);
		b4.setLocation(100, 210);
		c.add(b4);
		
		b3.setBounds(60, 220, 150, 100);
		b4.setBounds(220, 250, 150, 45);
		
		JLabel b5 = new JLabel("�н� �����"); // ��ư ����
		b5.setFont(new Font("���� ���", Font.BOLD, 25));
		b5.setLocation(100, 210); // ��ư�� ��ġ ����
		c.add(b5);
		JTextField b6 = new JTextField(20);
		b6.setLocation(100, 210);
		c.add(b6);
		
		b5.setBounds(60, 300, 150, 100);
		b6.setBounds(220, 330, 150, 45);
		
		JLabel b7 = new JLabel("���� Ǯ��Ƚ��"); // ��ư ����
		b7.setFont(new Font("���� ���", Font.BOLD, 25));
		b7.setLocation(100, 210); // ��ư�� ��ġ ����
		c.add(b7);
		JTextField b8 = new JTextField(20);
		b8.setLocation(100, 210);
		c.add(b8);
		
		b7.setBounds(60, 380, 200, 100);
		b8.setBounds(220, 410, 150, 45);
		
		setSize(420, 550); // ������ ũ��
		
		setVisible(true); // ������ ȭ�� ���
	}
	
class MyPanel extends JPanel {
		
		ImageIcon icon = new ImageIcon("images/house.png");
		Image img = icon.getImage();
		
		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			g.setColor(Color.BLACK);
			g.fillRect(0, 0, 420, 50);
			g.drawImage(img, 20,20, 30, 30, this);
			g.setColor(Color.WHITE);
			g.setFont(new Font("���� ���", Font.BOLD, 25));
			g.drawString("��ǥ ������ Ȯ��", 110, 40);
		}
		}
	
	public static void main(String [] args) {
		new CheckStudyPlan();
	}
}*/

package LearningPlanner;

import javax.swing.*;
import LearningPlanner.SetStudyPlan.RoundedButton;
import LearningPlanner.SetStudyPlan.barPanel;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

import MainDisplay.*;
import LearningPlanner.SetStudyPlan;

public class CheckStudyPlan extends SetStudyPlan {

	JLabel f1, f2, f3, f4;
	RoundedButton save;

	public void CheckStudyPlan() {
		// # 0. �⺻ ����
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(null);

		// # 1. ��Ʈ ����
		Font headerFont = new Font("���� ���", Font.BOLD, 20);
		Font contentFont = new Font("���� ���", Font.BOLD, 25);

		// # 2. ��� ����
		// # 2-1. ��� ����
		JLabel headerTitle = new JLabel("��ǥ ������ Ȯ��");
		headerTitle.setLocation(125, -25);
		headerTitle.setSize(200, 100);
		headerTitle.setFont(headerFont);
		headerTitle.setForeground(Color.WHITE);
		c.add(headerTitle);

		// # 2-2. ��� ������ �г�
		// ������ �г�(Ȩ ��ư, ���� Ǭ �� ����)
		JPanel header = new JPanel();
		header.setLocation(0, 0);
		header.setSize(420, 50);
		header.setBackground(Color.BLACK);

		// # 2-3. Home ��ư
		JButton homeButton = new JButton(new ImageIcon("Images/home.png"));
		homeButton.setLocation(10, 5);
		homeButton.setBackground(Color.BLACK);
		homeButton.setSize(42, 42);
		homeButton.setBorderPainted(false);
		homeButton.setFocusPainted(false);

		// # 3. �ߴ� ����
		// # 3.1 ��ǥ �ð�
		JLabel time = new JLabel("��ǥ �ð�");
		time.setLocation(50, 145);
		time.setSize(200, 40);
		time.setFont(contentFont);
		c.add(time);

		// # 3.2 �н� �ܾ
		JLabel wordcount = new JLabel("�н� �ܾ");
		wordcount.setLocation(50, 225);
		wordcount.setSize(200, 40);
		wordcount.setFont(contentFont);
		c.add(wordcount);

		// # 3.3 ��ǥ �����
		JLabel scorerate = new JLabel("��ǥ �����");
		scorerate.setLocation(50, 305);
		scorerate.setSize(200, 40);
		scorerate.setFont(contentFont);
		c.add(scorerate);

		// # 3.4 ���� Ǯ��Ƚ��
		JLabel quizplaynum = new JLabel("���� Ǯ��Ƚ��");
		quizplaynum.setLocation(50, 385);
		quizplaynum.setSize(200, 40);
		quizplaynum.setFont(contentFont);
		c.add(quizplaynum);

		// # 4. �ߴ� �Է¶�
		// # 4.1. �ߴ� ù��° �Է¶�
		f1 = new JLabel();
		f1.setHorizontalAlignment(JTextField.RIGHT);
		f1.setLocation(200, 145);
		f1.setSize(170, 40);
		f1.setFont(contentFont);
		c.add(f1);

		// # 3-2. ���� ��
		barPanel b1 = new barPanel();
		b1.setLayout(null);
		b1.setSize(295, 30);
		b1.setLocation(80, 165);
		c.add(b1);

		// # 4.2. �ߴ� ù��° �Է¶�
		f2 = new JLabel();
		f2.setHorizontalAlignment(JTextField.RIGHT);
		f2.setLocation(200, 225);
		f2.setSize(170, 40);
		f2.setFont(contentFont);
		c.add(f2);

		// # 3-2. ���� ��
		barPanel b2 = new barPanel();
		b2.setLayout(null);
		b2.setSize(295, 30);
		b2.setLocation(80, 245);
		c.add(b2);

		// # 4.3. �ߴ� ù��° �Է¶�
		f3 = new JLabel();
		f3.setHorizontalAlignment(JTextField.RIGHT);
		f3.setLocation(200, 305);
		f3.setSize(170, 40);
		f3.setFont(contentFont);
		c.add(f3);

		// # 3-2. ���� ��
		barPanel b3 = new barPanel();
		b3.setLayout(null);
		b3.setSize(295, 30);
		b3.setLocation(80, 325);
		c.add(b3);

		// # 4.4. �ߴ� ù��° �Է¶�
		f4 = new JLabel();
		f4.setHorizontalAlignment(JTextField.RIGHT);
		f4.setLocation(220, 385);
		f4.setSize(150, 40);
		f4.setFont(contentFont);
		c.add(f4);

		// # 3-2. ���� ��
		barPanel b4 = new barPanel();
		b4.setLayout(null);
		b4.setSize(275, 30);
		b4.setLocation(100, 405);
		c.add(b4);

		// # 5. ���� ��ư
		save = new RoundedButton("�ҷ�����");
		save.setLocation(140, 445);
		save.setBackground(new Color(112, 173, 71));
		save.setSize(125, 45);
		save.setFont(contentFont);
		save.setForeground(Color.WHITE);
		c.add(save);

		// Home ��ư �̺�Ʈ �߰�
		homeButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. ������������ �̵��ϱ�
				new MainDisplay();
				setVisible(false); // �ش� â �Ⱥ��̱�
			}
		});

		save.addActionListener(this);

		c.add(header);
		c.add(homeButton);

		setTitle("���� ��!! VOCA");
		setSize(420, 550); // ������ ũ��
		setResizable(false); // â�� ũ�⸦ �������� ���ϵ��� ����
		setVisible(true); // ������ ȭ�� ���
	}

	public static void main(String[] args) {
		new CheckStudyPlan();
	}

	public void actionPerformed(ActionEvent e) {

		FileDialog dialog = new FileDialog(this, "�ҷ�����", FileDialog.LOAD);
		dialog.setFile("*.txt;");
		dialog.setVisible(true);

		String path = dialog.getDirectory() + dialog.getFile();
		String s1 = "";
		String s2 = "";
		String s3 = "";
		String s4 = "";

		if (dialog.getFile() == null)
			return;

		try {

			FileReader r = new FileReader(path);

			int k;

			for (;;) {
				k = r.read();
				char charData = (char) k;
				if (charData == ' ')
					break;
				s1 += (char) k;
			}
			for (;;) {
				k = r.read();
				char charData = (char) k;
				if (charData == ' ')
					break;
				s2 += (char) k;
			}
			for (;;) {
				k = r.read();
				char charData = (char) k;
				if (charData == ' ')
					break;
				s3 += (char) k;
			}
			for (;;) {
				k = r.read();
				if (k == -1)
					break;
				s4 += (char) k;
			}

			r.close();

		} catch (Exception e2) {
			System.out.println("����" + e);
		}

		f1.setText(s1);
		f2.setText(s2);
		f3.setText(s3);
		f4.setText(s4);

	}

}
