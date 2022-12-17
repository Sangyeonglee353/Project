/*package LearningPlanner;

import javax.swing.*;
import java.awt.*;


public class SetStudyPlan extends JFrame {

	public SetStudyPlan() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setContentPane(new MyPanel());
		
		Container c = getContentPane();
		c.setLayout(null);
		
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
			g.fillRect(0, 0, 420, 65);
			g.drawImage(img, 20,20, 30, 30, this);
			g.setColor(Color.WHITE);
			g.setFont(new Font("맑은 고딕", Font.BOLD, 25));
			g.drawString("학습량 설정", 130, 40);
		}
	}
	
	public static void main(String [] args) {
		new SetStudyPlan();
	}
}*/

package LearningPlanner;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import MainDisplay.*;
import Quiz.Quiz;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.*;

public class SetStudyPlan extends JFrame implements ActionListener {

	JTextField f1, f2, f3, f4;
	RoundedButton save;

	public void SetStudyPlan() {
		// # 0. 기본 설정
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(null);

		// # 1. 폰트 설정
		Font headerFont = new Font("맑은 고딕", Font.BOLD, 20);
		Font contentFont = new Font("맑은 고딕", Font.BOLD, 25);

		// # 2. 상단 제목
		// # 2-1. 상단 제목
		JLabel headerTitle = new JLabel("학습량 설정");
		headerTitle.setLocation(145, -25);
		headerTitle.setSize(130, 100);
		headerTitle.setFont(headerFont);
		headerTitle.setForeground(Color.WHITE);
		c.add(headerTitle);

		// # 2-2. 상단 검은색 패널
		// 검은색 패널(홈 버튼, 문제 푼 수 포함)
		JPanel header = new JPanel();
		header.setLocation(0, 0);
		header.setSize(420, 50);
		header.setBackground(Color.BLACK);
		c.add(header);

		// # 2-3. Home 버튼
		JButton homeButton = new JButton(new ImageIcon("Images/home.png"));
		homeButton.setLocation(10, 5);
		homeButton.setBackground(Color.BLACK);
		homeButton.setSize(42, 42);
		homeButton.setBorderPainted(false);
		homeButton.setFocusPainted(false);
		c.add(homeButton);

		// # 3. 중단 내용
		// # 3.1 목표 시간
		JLabel time = new JLabel("목표시간");
		time.setLocation(50, 145);
		time.setSize(100, 40);
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
		f1 = new JTextField("하루00시간", 20);
		f1.setHorizontalAlignment(JTextField.RIGHT);
		f1.setLocation(200, 145);
		f1.setSize(170, 40);
		f1.setFont(contentFont);
		c.add(f1);

		// # 4.2. 중단 첫번째 입력란
		f2 = new JTextField("00개", 20);
		f2.setHorizontalAlignment(JTextField.RIGHT);
		f2.setLocation(200, 225);
		f2.setSize(170, 40);
		f2.setFont(contentFont);
		c.add(f2);

		// # 4.3. 중단 첫번째 입력란
		f3 = new JTextField("00%", 20);
		f3.setHorizontalAlignment(JTextField.RIGHT);
		f3.setLocation(200, 305);
		f3.setSize(170, 40);
		f3.setFont(contentFont);
		c.add(f3);

		// # 4.4. 중단 첫번째 입력란
		f4 = new JTextField("00회", 20);
		f4.setHorizontalAlignment(JTextField.RIGHT);
		f4.setLocation(220, 385);
		f4.setSize(150, 40);
		f4.setFont(contentFont);
		c.add(f4);

		// # 5. 저장 버튼
		save = new RoundedButton("저장");
		save.setLocation(140, 445);
		save.setBackground(new Color(112, 173, 71));
		save.setSize(125, 45);
		save.setFont(contentFont);
		save.setForeground(Color.WHITE);
		c.add(save);

		// # 6. Home 버튼 이벤트 추가
		homeButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. 메인페이지로 이동하기
				new MainDisplay();
				setVisible(false); // 해당 창 안보이기
			}
		});

		save.addActionListener(this);

		setTitle("이젠 해!! VOCA");
		setSize(420, 550); // 프레임 크기
		setResizable(false); // 창의 크기를 변경하지 못하도록 설정
		setVisible(true); // 프레임 화면 출력
	}

	public void SaveStudyPlan() {
		// # 0. 기본 설정
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(null);

		// # 1. 폰트 설정
		Font headerFont = new Font("맑은 고딕", Font.BOLD, 20);
		Font contentFont = new Font("맑은 고딕", Font.BOLD, 25);

		JLabel savecontent = new JLabel("정상처리 되었습니다");
		savecontent.setLocation(95, 180);
		savecontent.setSize(300, 150);
		savecontent.setFont(contentFont);
		savecontent.setForeground(Color.BLACK);
		c.add(savecontent);

		RoundedButton complete = new RoundedButton("확인");
		complete.setLocation(140, 290);
		complete.setBackground(new Color(112, 173, 71));
		complete.setSize(125, 45);
		complete.setFont(contentFont);
		complete.setForeground(Color.WHITE);
		c.add(complete);
		complete.setBorderPainted(false);
		complete.setFocusPainted(false);

		RoundedLabel a = new RoundedLabel();
		a.setLocation(60, 210);
		a.setBackground(Color.WHITE);
		a.setSize(300, 150);
		a.setFont(contentFont);
		a.setForeground(Color.BLACK);
		c.add(a);

		// # 불투명 처리
		JPanel opacity = new JPanel();
		opacity.setLocation(0, 50);
		opacity.setSize(420, 520);
		opacity.setBackground(new Color(0, 0, 0, 122));
		c.add(opacity);

		// # 2. 상단 제목
		// # 2-2. 상단 제목
		JLabel headerTitle = new JLabel("학습량 설정");
		headerTitle.setLocation(145, -25);
		headerTitle.setSize(130, 100);
		headerTitle.setFont(headerFont);
		headerTitle.setForeground(Color.WHITE);
		c.add(headerTitle);
		
		// # 2-1. 상단 검은색 패널
		// 검은색 패널(홈 버튼, 문제 푼 수 포함)
		JPanel header = new JPanel();
		header.setLocation(0, 0);
		header.setSize(420, 50);
		header.setBackground(Color.BLACK);
		c.add(header);

		// # 2-3. Home 버튼
		JButton homeButton = new JButton(new ImageIcon("Images/home.png"));
		homeButton.setLocation(10, 5);
		homeButton.setBackground(Color.BLACK);
		homeButton.setSize(42, 42);
		homeButton.setBorderPainted(false);
		homeButton.setFocusPainted(false);
		c.add(homeButton);

		// Home 버튼 이벤트 추가
		homeButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. 메인페이지로 이동하기
				new MainDisplay();
				setVisible(false); // 해당 창 안보이기
			}
		});

		// # 3. 중단 내용
		// # 3.1 목표 시간
		JLabel time = new JLabel("목표시간");
		time.setLocation(50, 145);
		time.setSize(100, 40);
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
		JLabel f1 = new JLabel("하루 00시간");
		f1.setHorizontalAlignment(JTextField.RIGHT);
		f1.setLocation(200, 145);
		f1.setSize(170, 40);
		f1.setFont(contentFont);
		c.add(f1);

		// # 4-2. 본문 바
		barPanel b1 = new barPanel();
		b1.setLayout(null);
		b1.setSize(295, 30);
		b1.setLocation(80, 165);
		c.add(b1);

		// # 4.2. 중단 첫번째 입력란
		JLabel f2 = new JLabel("00개");
		f2.setHorizontalAlignment(JTextField.RIGHT);
		f2.setLocation(200, 225);
		f2.setSize(170, 40);
		f2.setFont(contentFont);
		c.add(f2);

		// # 4-2. 본문 바
		barPanel b2 = new barPanel();
		b2.setLayout(null);
		b2.setSize(295, 30);
		b2.setLocation(80, 245);
		c.add(b2);

		// # 4.3. 중단 첫번째 입력란
		JLabel f3 = new JLabel("00개");
		f3.setHorizontalAlignment(JTextField.RIGHT);
		f3.setLocation(200, 305);
		f3.setSize(170, 40);
		f3.setFont(contentFont);
		c.add(f3);

		// # 4-2. 본문 바
		barPanel b3 = new barPanel();
		b3.setLayout(null);
		b3.setSize(295, 30);
		b3.setLocation(80, 325);
		c.add(b3);

		// # 4.4. 중단 첫번째 입력란
		JLabel f4 = new JLabel("00회");
		f4.setHorizontalAlignment(JTextField.RIGHT);
		f4.setLocation(220, 385);
		f4.setSize(150, 40);
		f4.setFont(contentFont);
		c.add(f4);

		// # 4-2. 본문 바
		barPanel b4 = new barPanel();
		b4.setLayout(null);
		b4.setSize(275, 30);
		b4.setLocation(100, 405);
		c.add(b4);

		// # 5. 저장 버튼
		RoundedButton save = new RoundedButton("저장");
		save.setLocation(140, 445);
		save.setBackground(new Color(112, 173, 71));
		save.setSize(125, 45);
		save.setFont(contentFont);
		save.setForeground(Color.WHITE);
		c.add(save);

		complete.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new MainDisplay();
				setVisible(false); // 해당 창 안보이기
			}
		});

		setTitle("이젠 해!! VOCA");
		setSize(420, 550); // 프레임 크기
		setResizable(false); // 창의 크기를 변경하지 못하도록 설정
		setVisible(true); // 프레임 화면 출력
	}

	// 메뉴바 클래스
	public class barPanel extends JPanel {
		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			g.setColor(Color.GRAY);
			g.fillRect(110, 20, 310, 3);
		}
	}

	// 라벨에 라운드 주기
	public class RoundedLabel extends JLabel {
		public RoundedLabel() {
			super();
		}

		public RoundedLabel(String text) {
			super(text);
		}

		public RoundedLabel(Icon icon) {
			super(icon);
		}

		@Override
		protected void paintComponent(Graphics g) {
			int width = getWidth();
			int height = getHeight();
			Graphics2D graphics = (Graphics2D) g;
			graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
			graphics.setColor(getBackground());
			graphics.fillRoundRect(0, 0, width, height, 30, 30);

			FontMetrics fontMetrics = graphics.getFontMetrics();
			Rectangle stringBounds = fontMetrics.getStringBounds(this.getText(), graphics).getBounds();
			int textX = (width - stringBounds.width) / 2;
			int textY = (height - stringBounds.height) / 2 + fontMetrics.getAscent();

			graphics.setColor(getForeground());
			graphics.setFont(getFont());
			graphics.drawString(getText(), textX, textY); // 버튼 글자 위치 조정
			graphics.dispose();
			super.paintComponent(g);

		}
	}

	// 버튼에 라운드 주기
	public class RoundedButton extends JButton {
		public RoundedButton() {
			super();
			decorate();
		}

		public RoundedButton(String text) {
			super(text);
			decorate();
		}

		public RoundedButton(Action action) {
			super(action);
			decorate();
		}

		public RoundedButton(Icon icon) {
			super(icon);
			decorate();
		}

		public RoundedButton(String text, Icon icon) {
			super(text, icon);
			decorate();
		}

		protected void decorate() {
			setBorderPainted(false);
			setOpaque(false);
		}

		@Override
		protected void paintComponent(Graphics g) {
			int width = getWidth();
			int height = getHeight();
			Graphics2D graphics = (Graphics2D) g;
			graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
			if (getModel().isArmed()) { // 마우스가 눌러진 상태
				graphics.setColor(getBackground().darker());
			} else if (getModel().isRollover()) { // 마우스가 올려진 상태
				graphics.setColor(getBackground().darker());
			} else { // 평상시
				graphics.setColor(getBackground());
			}

			graphics.fillRoundRect(0, 0, width, height, 30, 30);

			FontMetrics fontMetrics = graphics.getFontMetrics();
			Rectangle stringBounds = fontMetrics.getStringBounds(this.getText(), graphics).getBounds();
			int textX = (width - stringBounds.width) / 2;
			int textY = (height - stringBounds.height) / 2 + fontMetrics.getAscent();

			graphics.setColor(getForeground());
			graphics.setFont(getFont());
			graphics.drawString(getText(), textX, textY); // 버튼 글자 위치 조정
			graphics.dispose();
			super.paintComponent(g);

		}
	}

	public static void main(String[] args) {
		new SetStudyPlan();
	}

	public void actionPerformed(ActionEvent e) {

		FileDialog dialog = new FileDialog(this, "로드", FileDialog.SAVE);
		dialog.setVisible(true);

		String path = dialog.getDirectory() + dialog.getFile();

		try {

			FileWriter w = new FileWriter(path);
			String a = f1.getText();
			String b = f2.getText();
			String c = f3.getText();
			String d = f4.getText();
			w.write(a + " " + "\r\n");
			w.write(b + " " + "\r\n");
			w.write(c + " " + "\r\n");
			w.write(d);
			w.close();

		} catch (Exception e2) {

			System.out.println("저장오류" + e2);
		}
		SetStudyPlan savecomplete = new SetStudyPlan();
		savecomplete.SaveStudyPlan();
	}

}