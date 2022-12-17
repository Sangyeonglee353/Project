//package Quiz;
//import MainDisplay.*;
//import java.awt.Color;
//import java.awt.Container;
//import java.awt.Font;
//import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
//
//import javax.swing.ImageIcon;
//import javax.swing.JButton;
//import javax.swing.JFrame;
//import javax.swing.JLabel;
//import javax.swing.JPanel;
//
//public class ImageQuiz extends JFrame{
//	public ImageQuiz() 
//	{
//		setTitle("�̹��� ����");
//		setSize(420, 550); // ������ ũ�� 420 X 520
//		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Xâ ������ �ݱ�
//		Container contentPane = getContentPane();
//		contentPane.setBackground(Color.WHITE);
//		contentPane.setLayout(null);
//
//		// �ܾ� �� �������� â�� ����� ��.(�ϴ� JLabel�� �ۼ�)
//		ImageIcon img = new ImageIcon("Images/apple.png");
//		JLabel imageLabel1 = new JLabel(img);
//		imageLabel1.setLocation(80,90);
//		imageLabel1.setSize(250,250);
//		contentPane.add(imageLabel1);
//
//		// ������ ����(?/?)
//		JLabel la = new JLabel("�̹��� ����(?/?)");
//		la.setLocation(150,-20);
//		la.setSize(100,100);
//		la.setForeground(Color.WHITE);
//		contentPane.add(la);
//
//		// [Home ��ư]
//		JButton jb2 = new JButton(new ImageIcon("Images/home.png"));
//		jb2.setLocation(10,5);
//		jb2.setBackground(Color.BLACK);
//		jb2.setSize(42,42);
//		jb2.setBorderPainted(false);
//		jb2.setFocusPainted(false);
//		
//		// Home ��ư �̺�Ʈ �߰�
//		jb2.addActionListener(new ActionListener() {
//			@Override
//			public void actionPerformed(ActionEvent e) {
//				// 1. ������������ �̵��ϱ�
//				new MainDisplay();
//				setVisible(false); // �ش� â �Ⱥ��̱�
//			}
//		});
//		contentPane.add(jb2);
//
//		// ������ �г�(Ȩ ��ư, ���� Ǭ �� ����)
//		JPanel jp = new JPanel();
//		jp.setLocation(0,0);
//		jp.setSize(420,50);
//		jp.setBackground(Color.BLACK);
//		contentPane.add(jp);
//
//		//-----------------------------------------------------------------------------------------------(ȸ�� �г� ����)
//		// �ð�(?:?)
//		JLabel la2 = new JLabel("?:?");
//		la2.setLocation(10,20);
//		la2.setSize(100,100);
//		la2.setForeground(Color.WHITE);
//		contentPane.add(la2);
//
//		// ����
//		JLabel la3 = new JLabel("SCORE");
//		la3.setLocation(10,43);
//		la3.setSize(100,100);
//		la3.setForeground(Color.WHITE);
//		contentPane.add(la3);
//
//		// ���� ǥ�� (?/?)
//		JLabel la4 = new JLabel("?/?");
//		la4.setLocation(180,45);
//		la4.setSize(100,100);
//		la4.setForeground(Color.WHITE);
//		contentPane.add(la4);
//
//		// �Ͻ����� ��ư
//		JButton jb3 = new JButton(new ImageIcon("Button_Image/premium-icon-pause-button-3312070.png"));
//		jb3.setLocation(360,70);
//		jb3.setBackground(Color.GRAY);
//		jb3.setSize(30,30);
//		jb3.setBorderPainted(false);
//		jb3.setFocusPainted(false);
//		contentPane.add(jb3);
//
//		// ȸ�� �г�(�ð�, ����, �Ͻ����� ����)
//		JPanel jp2 = new JPanel();
//		jp2.setLocation(0,50);
//		jp2.setSize(420,65);
//		jp2.setBackground(Color.GRAY);
//		contentPane.add(jp2);
//		
//		// ������ ��ư
//		int x = 50; // x��ǥ
//		int y = 315; // y��ǥ 
//		for(int i = 1; i <= 3; i++)
//		{
//			JButton button = new JButton(Integer.toString(i));
//			button.setLocation(x, y);
//			button.setSize(300, 55); 
//			button.setBackground(new Color(208,206,206));
//			contentPane.add(button);
//			y += 65;
//		}
//
//		setVisible(true);
//		setResizable(false); // â�� ũ�⸦ �������� ���ϵ��� ����
//	}
//	public static void main(String[] args) {
//		new ImageQuiz();
//	}
//}

package Quiz;
import MainDisplay.*;

import java.awt.Color;
import java.awt.Container;
import java.awt.Font;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;
import java.util.Scanner;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import MainDisplay.MainDisplay;

public class ImageQuiz extends JFrame{
	private int vocaNum = 10; // �ܾ� ����
	private String [] English_words = new String[vocaNum]; // ���� �ܾ� �迭
	private String [] Korean_words = new String[vocaNum];  // �ѱ� �� �迭
	
	/* �̹��� ũ�� ������ ���� throws IOException �߰�*/
	public ImageQuiz(String vocaName)
	{
		// #1. ���Ͽ��� �ܾ� ��������
		try {
			File file = new File("voca\\" + vocaName + ".txt");
			
			Scanner scanner = new Scanner(new InputStreamReader(new FileInputStream(file), "UTF-8"));
			
			int englishNum = 0; // ���� �ܾ� ���� ����
			int koreanNum = 0; // �ѱ� �� ���� ����
			
			for(int i = 0; i < 20; i++) {
				String word = scanner.nextLine(); // �� �پ� �о����
				int k = i + 1;
				
				if(k % 2 != 0) { 
					English_words[englishNum++] = word; // �迭�� ���� �ܾ� ����
				}
				else {
					Korean_words[koreanNum++] = word; // �迭�� �ѱ� �� ����
				}
			}
			scanner.close(); // scanner ��Ʈ�� �ݱ�
		}
		catch (IOException e) {
			System.out.println("����� ����");
		}
		/* ���� ���� ���� */
		Random r = new Random();
		int random_word_number = 0;
		int random_korea_number = 0;
		
		/* JFrame ���� */
		setTitle("���� ��!! VOCA");
		setSize(420, 550); // ������ ũ�� 420 X 520
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Xâ ������ �ݱ�
		Container contentPane = getContentPane();
		contentPane.setBackground(Color.WHITE);
		contentPane.setLayout(null);

		// �ܾ� �� �������� â�� ����� ��.(�ϴ� JLabel�� �ۼ�)
		random_word_number = r.nextInt(10);
		String englishWord = English_words[random_word_number];
		// �̹����� ���� ũ��� ����
		ImageIcon icon = new ImageIcon("Images/vocaImages/" + englishWord + ".jpg");
		Image img = icon.getImage();
		// ���� �������� 260,160�� ���缭 �̹����� ����
		Image changeImg = img.getScaledInstance(260, 160, Image.SCALE_SMOOTH);
		ImageIcon changeIcon = new ImageIcon(changeImg);
		JLabel imageLabel1 = new JLabel(changeIcon);
		imageLabel1.setLocation(70,135);
		imageLabel1.setSize(260,160);
		contentPane.add(imageLabel1);
			
		// �̹��� ����(?/?)
		JLabel la = new JLabel("�̹��� ����(1/" + vocaNum + ")");
		la.setLocation(130,-25);
		la.setSize(180,100);
		la.setForeground(Color.WHITE);
		la.setFont(new Font("���� ���", Font.BOLD, 20));
		contentPane.add(la);

		// Home ��ư
		JButton jb2 = new JButton(new ImageIcon("Images/home.png"));
		jb2.setLocation(10,5);
		jb2.setBackground(Color.BLACK);
		jb2.setSize(42,42);
		jb2.setBorderPainted(false);
		jb2.setFocusPainted(false);
		contentPane.add(jb2);
		
		// Home ��ư �̺�Ʈ �߰�
		jb2.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. ������������ �̵��ϱ�
				new MainDisplay();
				setVisible(false); // �ش� â �Ⱥ��̱�
			}
		});

		// ������ �г�(Ȩ ��ư, ���� Ǭ �� ����)
		JPanel jp = new JPanel();
		jp.setLocation(0,0);
		jp.setSize(420,50);
		jp.setBackground(Color.BLACK);
		contentPane.add(jp);

		//-----------------------------------------------------------------------------------------------(ȸ�� �г� ����)
		// �ð�(?:?)
		JLabel la2 = new JLabel("00:00");
		la2.setLocation(10,15);
		la2.setSize(100,100);
		la2.setForeground(Color.WHITE);
		la2.setFont(new Font("���� ���", Font.BOLD, 18));
		contentPane.add(la2);

		// ����
		JLabel la3 = new JLabel("SCORE");
		la3.setLocation(10,45);
		la3.setSize(100,100);
		la3.setForeground(Color.WHITE);
		la3.setFont(new Font("���� ���", Font.BOLD, 15));
		contentPane.add(la3);

		// ���� ǥ�� (?/?)
		JLabel la4 = new JLabel("0/"+ vocaNum);
		la4.setLocation(180,45);
		la4.setSize(100,100);
		la4.setForeground(Color.WHITE);
		la4.setFont(new Font("���� ���", Font.BOLD, 15));
		contentPane.add(la4);

		// �Ͻ����� ��ư
		JButton jb3 = new JButton(new ImageIcon("Images/pause.png"));
		jb3.setLocation(360,70);
		jb3.setBackground(Color.GRAY);
		jb3.setSize(30,30);
		jb3.setBorderPainted(false);
		jb3.setFocusPainted(false);
		contentPane.add(jb3);

		// ȸ�� �г�(�ð�, ����, �Ͻ����� ����)
		JPanel jp2 = new JPanel();
		jp2.setLocation(0,50);
		jp2.setSize(420,65);
		jp2.setBackground(Color.GRAY);
		contentPane.add(jp2);
		
		// ������ ��ư
		//int x = 50; // x��ǥ
		//int y = 315; // y��ǥ 
//		for(int i = 1; i <= 3; i++)
//		{
//			JButton button = new JButton(Integer.toString(i));
//			button.setLocation(x, y);
//			button.setSize(300, 55); 
//			button.setBackground(new Color(208,206,206));
//			contentPane.add(button);
//			y += 65;
//		}
		
//-----------------------------------------------------------------------------------------------(��ư ����)
		// ������ ��ư
		Random r2 = new Random();
		int x = 50; // x��ǥ
		int y = 315; // ����1�� y��ǥ 
		int y2 = y+65; // ����2�� y��ǥ
		int y3 = y2+65; // ����3�� y��ǥ
		//int y4 = 440; // ����4�� y��ǥ
		int sum = 0; // ���� ���⸦ �����ϱ� ���� �ʿ��� ����
		int example[] = {y, y2, y3};
		
		int korean_example[] = new int[3]; // �ѱ� �� ����(0 ~ 3)
		int y_coordinate[] = new int[2]; // y ��ǥ(245, 310, 375 �� 2��) �� ������ �ƴ� ������ ��Ÿ���� y��ǥ 3��
		int correct_number; // ����
		
		// ������ 3���� ����
		for(int i = 0; i < 3; i++) 
		{
			korean_example[i] = r2.nextInt(10);
			
			for(int j = 0; j < i; j++)
			{
				if(korean_example[i] == korean_example[j] || korean_example[i] == random_word_number)
				{
					i--;
					break;
				}
			}
			
		}
		// ������ 2���� y��ǥ
		for(int i = 0; i < 2; i++) 
		{
			y_coordinate[i] = r2.nextInt(3); // 0 ~ 2������ ���� ���ڰ� y_coordinate �迭�� ��
			
			for(int j = 0; j < i; j++)
			{
				if(y_coordinate[i] == y_coordinate[j])
				{
					i--;
					break;
				}
			}
		}
	
		for(int i = 0; i < 2; i++)
		{
			sum += y_coordinate[i];
		}
		if(sum == 1) correct_number = 2;
		else if(sum == 2) correct_number = 1;
		else correct_number = 0;
		//else correct_number = 1;

		// ������ �ƴ� ���� 2�� ���
		for(int i = 0; i < 2; i++)
		{
			JButton button = new JButton(Korean_words[korean_example[i]]);
			button.setLocation(x, example[y_coordinate[i]]);
			button.setSize(300, 55);
			button.setFont(new Font("���� ���", Font.BOLD, 15));
			button.setBackground(new Color(208,206,206));
			contentPane.add(button);
			button.addMouseListener(new MouseListener() {
				public void mousePressed(MouseEvent e) { // ���콺 ��ư�� �������� ��
					button.setBackground(new Color(255, 192, 0));
				}
				public void mouseReleased(MouseEvent e) { // ������ ��ư�� ������ ��
					button.setBackground(new Color(255, 192, 0));
				}
				public void mouseClicked(MouseEvent e) { // ���콺�� ������Ʈ�� Ŭ���Ͽ��� ��
					
				}
				public void mouseEntered(MouseEvent e) { // ���콺�� ������Ʈ ���� �ö� ��
					//button.setBackground(new Color(112, 173, 71));
				}
				public void mouseExited(MouseEvent e) { // ���콺�� ������Ʈ���� ������ ��
					//button.setBackground(new Color(208, 206, 206));
				}
			});
			
		}
		
		// ���� ���
		JButton button = new JButton(Korean_words[random_word_number]);
		button.setLocation(x, example[correct_number]);
		button.setSize(300, 55);
		button.setFont(new Font("���� ���", Font.BOLD, 15));
		button.setBackground(new Color(208,206,206));
		button.addMouseListener(new MouseListener() {
			public void mousePressed(MouseEvent e) { // ���콺 ��ư�� �������� ��
				button.setBackground(new Color(112, 173, 71));
			}
			public void mouseReleased(MouseEvent e) { // ������ ��ư�� ������ ��
				button.setBackground(new Color(112, 173, 71));
			}
			public void mouseClicked(MouseEvent e) { // ���콺�� ������Ʈ�� Ŭ���Ͽ��� ��
				
			}
			public void mouseEntered(MouseEvent e) { // ���콺�� ������Ʈ ���� �ö� ��
				//button.setBackground(new Color(112, 173, 71));
			}
			public void mouseExited(MouseEvent e) { // ���콺�� ������Ʈ���� ������ ��
				//button.setBackground(new Color(208, 206, 206));
			}
		});
		contentPane.add(button);		
//-----------------------------------------------------------------------------------------------(��ư ����)
		setVisible(true);
		setResizable(false); // â�� ũ�⸦ �������� ���ϵ��� ����
	}

}
