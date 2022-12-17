package Quiz;
import java.awt.Color;
import java.awt.Container;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

/* 단어 읽어오기 위해 삽입 */
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;
import java.util.Scanner;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

/* 소리 재생을 위해 삽입 */
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;

import MainDisplay.MainDisplay;

public class MultipleChoiceQuiz extends JFrame {	
	public static boolean inputCheck;
	private int vocaNum = 10; // 단어 개수
	private String [] English_words = new String[vocaNum]; // 영어 단어 배열
	private String [] Korean_words = new String[vocaNum];  // 한글 뜻 배열
	
	public MultipleChoiceQuiz(String vocaName) 
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
		
		// 추후에 더 많은 영어 데이터 베이스 가져오기
		//String[] English_words = {"introduce", "reception", "regardness", "butterfly", "complete", "decay", "event", "manipulate", "eliminate", "alternative"};
		//String[] Korean_words = {"소개하다", "명성", "간주하다", "나비", "완성하다", "부패하다", "사건", "조종하다", "제거하다", "대안"};
		Random r = new Random();
		int random_word_number = 0;
		int random_korea_number = 0;
		
		setTitle("이젠 해!! VOCA");
		setSize(420, 550); // 프레임 크기 420 X 520
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // X창 누르면 닫기
		Container contentPane = getContentPane();
		contentPane.setBackground(Color.WHITE);
		contentPane.setLayout(null);
		
		// 단어 문자열의 개수에 따라 보기좋게 출력하기 위한 3개의 if문
		random_word_number = r.nextInt(10);
		String englishWord = English_words[random_word_number];
		if(englishWord.length() <= 5) // 단어의 문자수가 5개 이하이면
		{
			// 단어 → 랜덤으로 창에 띄워야 함.(일단 JLabel로 작성)
			JLabel word = new JLabel(englishWord);
			word.setLocation(145,70);
			word.setSize(250, 230);
			word.setFont(new Font("Serif", Font.BOLD, 45));
			word.setForeground(Color.BLACK);
			contentPane.add(word);
		}
		if(englishWord.length() > 5 && englishWord.length() <= 9) // 단어의 문자수가 5개 이상, 9개 이하이면
		{
			// 단어 → 랜덤으로 창에 띄워야 함.(일단 JLabel로 작성)
			JLabel word = new JLabel(englishWord);
			word.setLocation(110,70);
			word.setSize(250, 230);
			word.setFont(new Font("Serif", Font.BOLD, 45));
			word.setForeground(Color.BLACK);
			contentPane.add(word);
		}
		if(englishWord.length() >= 10) // 단어의 문자수가 10개 이상이면
		{
			// 단어 → 랜덤으로 창에 띄워야 함.(일단 JLabel로 작성)
			JLabel word = new JLabel(englishWord);
			word.setLocation(95,70);
			word.setSize(250, 230);
			word.setFont(new Font("Serif", Font.BOLD, 45));
			word.setForeground(Color.BLACK);
			contentPane.add(word);
		}
//-----------------------------------------------------------------------------------------------(검은색 패널 구현)
		
		// 객관식 퀴즈(?/?)
		JLabel la = new JLabel("객관식 퀴즈(1/"+ vocaNum+ ")");
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
		jb3.setLocation(350,60);
		jb3.setBackground(Color.GRAY);
		jb3.setSize(50,50);
		jb3.setBorderPainted(false);
		jb3.setFocusPainted(false);
		contentPane.add(jb3);
		
		// 회색 패널(시간, 점수, 일시정지 포함)
		JPanel jp2 = new JPanel();
		jp2.setLocation(0,50);
		jp2.setSize(420,65);
		jp2.setBackground(Color.GRAY);
		contentPane.add(jp2);
		
		// speaker 버튼
		JButton jb4 = new JButton(new ImageIcon("Images/speaker.png"));
		jb4.setLocation(10,120);
		jb4.setSize(50,50);
		jb4.setBackground(Color.white);
		jb4.setBorderPainted(false);
		jb4.setFocusPainted(false);
		
		// speaker 버튼에 이벤트 추가
		jb4.addMouseListener(new MouseListener() {
			public void mousePressed(MouseEvent e) {
		        File file = new File("voices/" + englishWord+ ".wav");
		        //System.out.println(file.exists()); // 파일 존재여부 체크
		        
		        try { 
		            AudioInputStream stream = AudioSystem.getAudioInputStream(file);
		            Clip clip = AudioSystem.getClip();
		            clip.open(stream);
		            clip.start();
		            
		        } catch(Exception k) {
		            
		            k.printStackTrace();
		        }
			}
			public void mouseReleased(MouseEvent e) {
				
			}
			public void mouseClicked(MouseEvent e) {
				
			}
			public void mouseEntered(MouseEvent e) {
				
			}
			public void mouseExited(MouseEvent e) {
				
			}
		});
		contentPane.add(jb4);
		
		
//-----------------------------------------------------------------------------------------------(버튼 구현)
		// 객관식 버튼
		Random r2 = new Random();
		int x = 50; // x좌표
		int y = 245; // 보기1의 y좌표 
		int y2 = 310; // 보기2의 y좌표
		int y3 = 375; // 보기3의 y좌표
		int y4 = 440; // 보기4의 y좌표
		int sum = 0; // 정답 보기를 구현하기 위해 필요한 변수
		int example[] = {y, y2, y3, y4};
		
		int korean_example[] = new int[4]; // 한국 뜻 보기(0 ~ 4)
		int y_coordinate[] = new int[3]; // y 좌표(245, 310, 375, 440 중 3개) → 정답이 아닌 오답을 나타내는 y좌표 3개
		int correct_number; // 정답
		
		// 랜덤의 4개의 숫자
		for(int i = 0; i < 4; i++) 
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
		// 랜덤의 3개의 y좌표
		for(int i = 0; i < 3; i++) 
		{
			y_coordinate[i] = r2.nextInt(4); // 0 ~ 3까지의 랜덤 숫자가 y_coordinate 배열에 들어감
			
			for(int j = 0; j < i; j++)
			{
				if(y_coordinate[i] == y_coordinate[j])
				{
					i--;
					break;
				}
			}
		}
	
		for(int i = 0; i < 3; i++)
		{
			sum += y_coordinate[i];
		}
		if(sum == 3) correct_number = 3;
		else if(sum == 4) correct_number = 2;
		else if(sum == 6) correct_number = 0;
		else correct_number = 1;

		// 정답이 아닌 보기 3개 출력
		for(int i = 0; i < 3; i++)
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
//					JButton checkX = new JButton(new ImageIcon("Images/xmark.png"));
//					checkX.setLocation(85, 50);
//					checkX.setSize(250, 250);
//					checkX.setBorderPainted(false); // 외곽선 제거
//					checkX.setContentAreaFilled(false); // 내용영역 채우기 제거
//					checkX.setFocusPainted(false); // 선택(focus)되었을 때 생기는 테두리 제거
//					contentPane.add(checkX);
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
	
//	public static void main(String[] args) {
//		new MultipleChoiceQuiz();
//	}
}
