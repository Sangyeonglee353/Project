/*package LearningPlanner;

import javax.swing.*;
import java.awt.*;

public class CheckStudyPlan extends JFrame {
	private String [] fruits = {"2021-11-14 일요일", "2021-11-15 월요일", "2021-11-16 화요일"}; 
	
	public CheckStudyPlan() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setContentPane(new MyPanel());
		
		Container c = getContentPane();
		c.setLayout(null);

		JComboBox<String> combo = new JComboBox<String>(fruits);
		c.add(combo);
		combo.setBounds(145, 105, 130, 30);
		
		JLabel b1 = new JLabel("목표시간"); // 버튼 생성
		b1.setFont(new Font("맑은 고딕", Font.BOLD, 25));
		b1.setLocation(100, 210); // 버튼의 위치 설정
		c.add(b1);
		JTextField b2 = new JTextField(20);
		b1.setLocation(100, 210);
		c.add(b2);
		
		b1.setBounds(60, 140, 100, 100);
		b2.setBounds(220, 170, 150, 45);
		
		JLabel b3 = new JLabel("학습 단어량"); // 버튼 생성
		b3.setFont(new Font("맑은 고딕", Font.BOLD, 25));
		b3.setLocation(100, 210); // 버튼의 위치 설정
		c.add(b3);
		JTextField b4 = new JTextField(20);
		b4.setLocation(100, 210);
		c.add(b4);
		
		b3.setBounds(60, 220, 150, 100);
		b4.setBounds(220, 250, 150, 45);
		
		JLabel b5 = new JLabel("학습 정답률"); // 버튼 생성
		b5.setFont(new Font("맑은 고딕", Font.BOLD, 25));
		b5.setLocation(100, 210); // 버튼의 위치 설정
		c.add(b5);
		JTextField b6 = new JTextField(20);
		b6.setLocation(100, 210);
		c.add(b6);
		
		b5.setBounds(60, 300, 150, 100);
		b6.setBounds(220, 330, 150, 45);
		
		JLabel b7 = new JLabel("퀴즈 풀이횟수"); // 버튼 생성
		b7.setFont(new Font("맑은 고딕", Font.BOLD, 25));
		b7.setLocation(100, 210); // 버튼의 위치 설정
		c.add(b7);
		JTextField b8 = new JTextField(20);
		b8.setLocation(100, 210);
		c.add(b8);
		
		b7.setBounds(60, 380, 200, 100);
		b8.setBounds(220, 410, 150, 45);
		
		setSize(420, 550); // 프레임 크기
		
		setVisible(true); // 프레임 화면 출력
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
			g.setFont(new Font("맑은 고딕", Font.BOLD, 25));
			g.drawString("목표 성취율 확인", 110, 40);
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
		// # 0. 기본 설정
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(null);

		// # 1. 폰트 설정
		Font headerFont = new Font("맑은 고딕", Font.BOLD, 20);
		Font contentFont = new Font("맑은 고딕", Font.BOLD, 25);

		// # 2. 상단 제목
		// # 2-1. 상단 제목
		JLabel headerTitle = new JLabel("목표 성취율 확인");
		headerTitle.setLocation(125, -25);
		headerTitle.setSize(200, 100);
		headerTitle.setFont(headerFont);
		headerTitle.setForeground(Color.WHITE);
		c.add(headerTitle);

		// # 2-2. 상단 검은색 패널
		// 검은색 패널(홈 버튼, 문제 푼 수 포함)
		JPanel header = new JPanel();
		header.setLocation(0, 0);
		header.setSize(420, 50);
		header.setBackground(Color.BLACK);

		// # 2-3. Home 버튼
		JButton homeButton = new JButton(new ImageIcon("Images/home.png"));
		homeButton.setLocation(10, 5);
		homeButton.setBackground(Color.BLACK);
		homeButton.setSize(42, 42);
		homeButton.setBorderPainted(false);
		homeButton.setFocusPainted(false);

		// # 3. 중단 내용
		// # 3.1 목표 시간
		JLabel time = new JLabel("목표 시간");
		time.setLocation(50, 145);
		time.setSize(200, 40);
		time.setFont(contentFont);
		c.add(time);

		// # 3.2 학습 단어량
		JLabel wordcount = new JLabel("학습 단어량");
		wordcount.setLocation(50, 225);
		wordcount.setSize(200, 40);
		wordcount.setFont(contentFont);
		c.add(wordcount);

		// # 3.3 목표 정답률
		JLabel scorerate = new JLabel("목표 정답률");
		scorerate.setLocation(50, 305);
		scorerate.setSize(200, 40);
		scorerate.setFont(contentFont);
		c.add(scorerate);

		// # 3.4 퀴즈 풀이횟수
		JLabel quizplaynum = new JLabel("퀴즈 풀이횟수");
		quizplaynum.setLocation(50, 385);
		quizplaynum.setSize(200, 40);
		quizplaynum.setFont(contentFont);
		c.add(quizplaynum);

		// # 4. 중단 입력란
		// # 4.1. 중단 첫번째 입력란
		f1 = new JLabel();
		f1.setHorizontalAlignment(JTextField.RIGHT);
		f1.setLocation(200, 145);
		f1.setSize(170, 40);
		f1.setFont(contentFont);
		c.add(f1);

		// # 3-2. 본문 바
		barPanel b1 = new barPanel();
		b1.setLayout(null);
		b1.setSize(295, 30);
		b1.setLocation(80, 165);
		c.add(b1);

		// # 4.2. 중단 첫번째 입력란
		f2 = new JLabel();
		f2.setHorizontalAlignment(JTextField.RIGHT);
		f2.setLocation(200, 225);
		f2.setSize(170, 40);
		f2.setFont(contentFont);
		c.add(f2);

		// # 3-2. 본문 바
		barPanel b2 = new barPanel();
		b2.setLayout(null);
		b2.setSize(295, 30);
		b2.setLocation(80, 245);
		c.add(b2);

		// # 4.3. 중단 첫번째 입력란
		f3 = new JLabel();
		f3.setHorizontalAlignment(JTextField.RIGHT);
		f3.setLocation(200, 305);
		f3.setSize(170, 40);
		f3.setFont(contentFont);
		c.add(f3);

		// # 3-2. 본문 바
		barPanel b3 = new barPanel();
		b3.setLayout(null);
		b3.setSize(295, 30);
		b3.setLocation(80, 325);
		c.add(b3);

		// # 4.4. 중단 첫번째 입력란
		f4 = new JLabel();
		f4.setHorizontalAlignment(JTextField.RIGHT);
		f4.setLocation(220, 385);
		f4.setSize(150, 40);
		f4.setFont(contentFont);
		c.add(f4);

		// # 3-2. 본문 바
		barPanel b4 = new barPanel();
		b4.setLayout(null);
		b4.setSize(275, 30);
		b4.setLocation(100, 405);
		c.add(b4);

		// # 5. 저장 버튼
		save = new RoundedButton("불러오기");
		save.setLocation(140, 445);
		save.setBackground(new Color(112, 173, 71));
		save.setSize(125, 45);
		save.setFont(contentFont);
		save.setForeground(Color.WHITE);
		c.add(save);

		// Home 버튼 이벤트 추가
		homeButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. 메인페이지로 이동하기
				new MainDisplay();
				setVisible(false); // 해당 창 안보이기
			}
		});

		save.addActionListener(this);

		c.add(header);
		c.add(homeButton);

		setTitle("이젠 해!! VOCA");
		setSize(420, 550); // 프레임 크기
		setResizable(false); // 창의 크기를 변경하지 못하도록 설정
		setVisible(true); // 프레임 화면 출력
	}

	public static void main(String[] args) {
		new CheckStudyPlan();
	}

	public void actionPerformed(ActionEvent e) {

		FileDialog dialog = new FileDialog(this, "불러오기", FileDialog.LOAD);
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
			System.out.println("오류" + e);
		}

		f1.setText(s1);
		f2.setText(s2);
		f3.setText(s3);
		f4.setText(s4);

	}

}
