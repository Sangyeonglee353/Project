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
//		setTitle("이미지 퀴즈");
//		setSize(420, 550); // 프레임 크기 420 X 520
//		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // X창 누르면 닫기
//		Container contentPane = getContentPane();
//		contentPane.setBackground(Color.WHITE);
//		contentPane.setLayout(null);
//
//		// 단어 → 랜덤으로 창에 띄워야 함.(일단 JLabel로 작성)
//		ImageIcon img = new ImageIcon("Images/apple.png");
//		JLabel imageLabel1 = new JLabel(img);
//		imageLabel1.setLocation(80,90);
//		imageLabel1.setSize(250,250);
//		contentPane.add(imageLabel1);
//
//		// 객관식 퀴즈(?/?)
//		JLabel la = new JLabel("이미지 퀴즈(?/?)");
//		la.setLocation(150,-20);
//		la.setSize(100,100);
//		la.setForeground(Color.WHITE);
//		contentPane.add(la);
//
//		// [Home 버튼]
//		JButton jb2 = new JButton(new ImageIcon("Images/home.png"));
//		jb2.setLocation(10,5);
//		jb2.setBackground(Color.BLACK);
//		jb2.setSize(42,42);
//		jb2.setBorderPainted(false);
//		jb2.setFocusPainted(false);
//		
//		// Home 버튼 이벤트 추가
//		jb2.addActionListener(new ActionListener() {
//			@Override
//			public void actionPerformed(ActionEvent e) {
//				// 1. 메인페이지로 이동하기
//				new MainDisplay();
//				setVisible(false); // 해당 창 안보이기
//			}
//		});
//		contentPane.add(jb2);
//
//		// 검은색 패널(홈 버튼, 문제 푼 수 포함)
//		JPanel jp = new JPanel();
//		jp.setLocation(0,0);
//		jp.setSize(420,50);
//		jp.setBackground(Color.BLACK);
//		contentPane.add(jp);
//
//		//-----------------------------------------------------------------------------------------------(회색 패널 구현)
//		// 시간(?:?)
//		JLabel la2 = new JLabel("?:?");
//		la2.setLocation(10,20);
//		la2.setSize(100,100);
//		la2.setForeground(Color.WHITE);
//		contentPane.add(la2);
//
//		// 점수
//		JLabel la3 = new JLabel("SCORE");
//		la3.setLocation(10,43);
//		la3.setSize(100,100);
//		la3.setForeground(Color.WHITE);
//		contentPane.add(la3);
//
//		// 점수 표기 (?/?)
//		JLabel la4 = new JLabel("?/?");
//		la4.setLocation(180,45);
//		la4.setSize(100,100);
//		la4.setForeground(Color.WHITE);
//		contentPane.add(la4);
//
//		// 일시정지 버튼
//		JButton jb3 = new JButton(new ImageIcon("Button_Image/premium-icon-pause-button-3312070.png"));
//		jb3.setLocation(360,70);
//		jb3.setBackground(Color.GRAY);
//		jb3.setSize(30,30);
//		jb3.setBorderPainted(false);
//		jb3.setFocusPainted(false);
//		contentPane.add(jb3);
//
//		// 회색 패널(시간, 점수, 일시정지 포함)
//		JPanel jp2 = new JPanel();
//		jp2.setLocation(0,50);
//		jp2.setSize(420,65);
//		jp2.setBackground(Color.GRAY);
//		contentPane.add(jp2);
//		
//		// 객관식 버튼
//		int x = 50; // x좌표
//		int y = 315; // y좌표 
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
//		setResizable(false); // 창의 크기를 변경하지 못하도록 설정
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
	private int vocaNum = 10; // 단어 개수
	private String [] English_words = new String[vocaNum]; // 영어 단어 배열
	private String [] Korean_words = new String[vocaNum];  // 한글 뜻 배열
	
	/* 이미지 크기 조절을 위해 throws IOException 추가*/
	public ImageQuiz(String vocaName)
	{
		// #1. 파일에서 단어 가져오기
		try {
			File file = new File("voca\\" + vocaName + ".txt");
			
			Scanner scanner = new Scanner(new InputStreamReader(new FileInputStream(file), "UTF-8"));
			
			int englishNum = 0; // 영어 단어 수량 변수
			int koreanNum = 0; // 한글 뜻 수량 변수
			
			for(int i = 0; i < 20; i++) {
				String word = scanner.nextLine(); // 한 줄씩 읽어오기
				int k = i + 1;
				
				if(k % 2 != 0) { 
					English_words[englishNum++] = word; // 배열에 영어 단어 저장
				}
				else {
					Korean_words[koreanNum++] = word; // 배열에 한글 뜻 저장
				}
			}
			scanner.close(); // scanner 스트림 닫기
		}
		catch (IOException e) {
			System.out.println("입출력 오류");
		}
		/* 랜덤 보기 설정 */
		Random r = new Random();
		int random_word_number = 0;
		int random_korea_number = 0;
		
		/* JFrame 설정 */
		setTitle("이젠 해!! VOCA");
		setSize(420, 550); // 프레임 크기 420 X 520
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // X창 누르면 닫기
		Container contentPane = getContentPane();
		contentPane.setBackground(Color.WHITE);
		contentPane.setLayout(null);

		// 단어 → 랜덤으로 창에 띄워야 함.(일단 JLabel로 작성)
		random_word_number = r.nextInt(10);
		String englishWord = English_words[random_word_number];
		// 이미지를 고정 크기로 삽입
		ImageIcon icon = new ImageIcon("Images/vocaImages/" + englishWord + ".jpg");
		Image img = icon.getImage();
		// 고정 사이즈인 260,160에 맞춰서 이미지를 변경
		Image changeImg = img.getScaledInstance(260, 160, Image.SCALE_SMOOTH);
		ImageIcon changeIcon = new ImageIcon(changeImg);
		JLabel imageLabel1 = new JLabel(changeIcon);
		imageLabel1.setLocation(70,135);
		imageLabel1.setSize(260,160);
		contentPane.add(imageLabel1);
			
		// 이미지 퀴즈(?/?)
		JLabel la = new JLabel("이미지 퀴즈(1/" + vocaNum + ")");
		la.setLocation(130,-25);
		la.setSize(180,100);
		la.setForeground(Color.WHITE);
		la.setFont(new Font("맑은 고딕", Font.BOLD, 20));
		contentPane.add(la);

		// Home 버튼
		JButton jb2 = new JButton(new ImageIcon("Images/home.png"));
		jb2.setLocation(10,5);
		jb2.setBackground(Color.BLACK);
		jb2.setSize(42,42);
		jb2.setBorderPainted(false);
		jb2.setFocusPainted(false);
		contentPane.add(jb2);
		
		// Home 버튼 이벤트 추가
		jb2.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. 메인페이지로 이동하기
				new MainDisplay();
				setVisible(false); // 해당 창 안보이기
			}
		});

		// 검은색 패널(홈 버튼, 문제 푼 수 포함)
		JPanel jp = new JPanel();
		jp.setLocation(0,0);
		jp.setSize(420,50);
		jp.setBackground(Color.BLACK);
		contentPane.add(jp);

		//-----------------------------------------------------------------------------------------------(회색 패널 구현)
		// 시간(?:?)
		JLabel la2 = new JLabel("00:00");
		la2.setLocation(10,15);
		la2.setSize(100,100);
		la2.setForeground(Color.WHITE);
		la2.setFont(new Font("맑은 고딕", Font.BOLD, 18));
		contentPane.add(la2);

		// 점수
		JLabel la3 = new JLabel("SCORE");
		la3.setLocation(10,45);
		la3.setSize(100,100);
		la3.setForeground(Color.WHITE);
		la3.setFont(new Font("맑은 고딕", Font.BOLD, 15));
		contentPane.add(la3);

		// 점수 표기 (?/?)
		JLabel la4 = new JLabel("0/"+ vocaNum);
		la4.setLocation(180,45);
		la4.setSize(100,100);
		la4.setForeground(Color.WHITE);
		la4.setFont(new Font("맑은 고딕", Font.BOLD, 15));
		contentPane.add(la4);

		// 일시정지 버튼
		JButton jb3 = new JButton(new ImageIcon("Images/pause.png"));
		jb3.setLocation(360,70);
		jb3.setBackground(Color.GRAY);
		jb3.setSize(30,30);
		jb3.setBorderPainted(false);
		jb3.setFocusPainted(false);
		contentPane.add(jb3);

		// 회색 패널(시간, 점수, 일시정지 포함)
		JPanel jp2 = new JPanel();
		jp2.setLocation(0,50);
		jp2.setSize(420,65);
		jp2.setBackground(Color.GRAY);
		contentPane.add(jp2);
		
		// 객관식 버튼
		//int x = 50; // x좌표
		//int y = 315; // y좌표 
//		for(int i = 1; i <= 3; i++)
//		{
//			JButton button = new JButton(Integer.toString(i));
//			button.setLocation(x, y);
//			button.setSize(300, 55); 
//			button.setBackground(new Color(208,206,206));
//			contentPane.add(button);
//			y += 65;
//		}
		
//-----------------------------------------------------------------------------------------------(버튼 구현)
		// 객관식 버튼
		Random r2 = new Random();
		int x = 50; // x좌표
		int y = 315; // 보기1의 y좌표 
		int y2 = y+65; // 보기2의 y좌표
		int y3 = y2+65; // 보기3의 y좌표
		//int y4 = 440; // 보기4의 y좌표
		int sum = 0; // 정답 보기를 구현하기 위해 필요한 변수
		int example[] = {y, y2, y3};
		
		int korean_example[] = new int[3]; // 한국 뜻 보기(0 ~ 3)
		int y_coordinate[] = new int[2]; // y 좌표(245, 310, 375 중 2개) → 정답이 아닌 오답을 나타내는 y좌표 3개
		int correct_number; // 정답
		
		// 랜덤의 3개의 숫자
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
		// 랜덤의 2개의 y좌표
		for(int i = 0; i < 2; i++) 
		{
			y_coordinate[i] = r2.nextInt(3); // 0 ~ 2까지의 랜덤 숫자가 y_coordinate 배열에 들어감
			
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

		// 정답이 아닌 보기 2개 출력
		for(int i = 0; i < 2; i++)
		{
			JButton button = new JButton(Korean_words[korean_example[i]]);
			button.setLocation(x, example[y_coordinate[i]]);
			button.setSize(300, 55);
			button.setFont(new Font("맑은 고딕", Font.BOLD, 15));
			button.setBackground(new Color(208,206,206));
			contentPane.add(button);
			button.addMouseListener(new MouseListener() {
				public void mousePressed(MouseEvent e) { // 마우스 버튼이 눌러졌을 때
					button.setBackground(new Color(255, 192, 0));
				}
				public void mouseReleased(MouseEvent e) { // 눌러진 버튼이 떼어질 때
					button.setBackground(new Color(255, 192, 0));
				}
				public void mouseClicked(MouseEvent e) { // 마우스로 컴포넌트를 클릭하였을 때
					
				}
				public void mouseEntered(MouseEvent e) { // 마우스가 컴포넌트 위에 올라갈 때
					//button.setBackground(new Color(112, 173, 71));
				}
				public void mouseExited(MouseEvent e) { // 마우스가 컴포넌트에서 내려올 때
					//button.setBackground(new Color(208, 206, 206));
				}
			});
			
		}
		
		// 정답 출력
		JButton button = new JButton(Korean_words[random_word_number]);
		button.setLocation(x, example[correct_number]);
		button.setSize(300, 55);
		button.setFont(new Font("맑은 고딕", Font.BOLD, 15));
		button.setBackground(new Color(208,206,206));
		button.addMouseListener(new MouseListener() {
			public void mousePressed(MouseEvent e) { // 마우스 버튼이 눌러졌을 때
				button.setBackground(new Color(112, 173, 71));
			}
			public void mouseReleased(MouseEvent e) { // 눌러진 버튼이 떼어질 때
				button.setBackground(new Color(112, 173, 71));
			}
			public void mouseClicked(MouseEvent e) { // 마우스로 컴포넌트를 클릭하였을 때
				
			}
			public void mouseEntered(MouseEvent e) { // 마우스가 컴포넌트 위에 올라갈 때
				//button.setBackground(new Color(112, 173, 71));
			}
			public void mouseExited(MouseEvent e) { // 마우스가 컴포넌트에서 내려올 때
				//button.setBackground(new Color(208, 206, 206));
			}
		});
		contentPane.add(button);		
//-----------------------------------------------------------------------------------------------(버튼 구현)
		setVisible(true);
		setResizable(false); // 창의 크기를 변경하지 못하도록 설정
	}

}
