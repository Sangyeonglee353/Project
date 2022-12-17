/*package LearningPlanner;

import javax.swing.*;
import MainDisplay.*;
import java.awt.*;
import java.awt.event.*;

public class LearningManagement extends JFrame {
	public LearningManagement() {
		// # 0. 기본 설정
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(null);
		
		// # 1. 폰트 설정
		Font headerFont = new Font("맑은 고딕", Font.BOLD, 20);
		Font contentFont = new Font("맑은 고딕", Font.BOLD, 25);
		Font menuFont = new Font("맑은 고딕", Font.BOLD, 45);
		
		// # 2. 상단 제목
		// # 2-1. 상단 검은색 패널
		// 검은색 패널(홈 버튼, 문제 푼 수 포함)
		JPanel header = new JPanel();
		header.setLocation(0,0);
		header.setSize(420,50);
		header.setBackground(Color.BLACK);

		// # 2-2. 상단 제목
		JLabel headerTitle = new JLabel("학습 플래너");
		headerTitle.setLocation(145, -25);
		headerTitle.setSize(130,100);
		headerTitle.setFont(headerFont);
		headerTitle.setForeground(Color.WHITE);
		c.add(headerTitle);
		
		// # 2-3. Home 버튼
		JButton homeButton = new JButton(new ImageIcon("Images/home.png"));
		homeButton.setLocation(10,5);
		homeButton.setBackground(Color.BLACK);
		homeButton.setSize(42,42);
		homeButton.setBorderPainted(false);
		homeButton.setFocusPainted(false);
		
		// Home 버튼 이벤트 추가
		homeButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. 메인페이지로 이동하기
				new MainDisplay();
				setVisible(false); // 해당 창 안보이기
			}
		});
		
		// # 3. 본문
		// # 3-1. 본문 제목
		JLabel contentTitle = new JLabel("나의 목표 관리");
		contentTitle.setLocation(120, 135);
		contentTitle.setSize(170,25);
		contentTitle.setFont(contentFont);
		contentTitle.setForeground(Color.BLACK);
		
		// # 3-2. 본문 바
		barPanel contentBar = new barPanel();
		contentBar.setLayout(null);
		contentBar.setSize(300, 30);
		contentBar.setLocation(0, 150);
		
		// # 4. 메뉴 버튼 
		// # 4-1. 학습량 설정 버튼
		PolygonButtonLeft leftMenu = new PolygonButtonLeft("학습량\n 설정"); // 버튼 생성
		leftMenu.setBackground(new Color(112,173,71));
		leftMenu.setForeground(Color.WHITE);
		leftMenu.setFont(menuFont);
		leftMenu.setLocation(0, 200); // 버튼의 위치 설정
		leftMenu.setSize(220, 200); // 
		
		// # 4-2. 목표 성취율 확인 버튼
		PolygonButtonRight rightMenu = new PolygonButtonRight("목표\n성취율\n확인"); // 버튼 생성
		rightMenu.setBackground(new Color(47,85,151));
		rightMenu.setForeground(Color.WHITE);
		rightMenu.setFont(menuFont);
		rightMenu.setLocation(180, 200); // 버튼의 위치 설정
		rightMenu.setSize(225, 200); // 
		
		// # 5. 컨텐트팬에 버튼 추가
		c.add(header);
		c.add(homeButton);
		c.add(contentTitle);
		c.add(contentBar);
		c.add(leftMenu);
		c.add(rightMenu);
		
		setTitle("이젠 해!! VOCA");
		setSize(420, 550); // 프레임 크기
		setResizable(false); // 창의 크기를 변경하지 못하도록 설정
		setVisible(true); // 프레임 화면 출력
	}
	
	// 메뉴바 클래스
	public class barPanel extends JPanel{
		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			g.setColor(Color.GRAY);
			g.fillRect(110, 20, 310, 3);
		}
	}
	// 좌측메뉴 버튼 클래스
	public class PolygonButtonLeft extends JButton{
		public PolygonButtonLeft() { super(); decorate(); } 
		  public PolygonButtonLeft(String text) { super(text); decorate(); } 
		  public PolygonButtonLeft(Action action) { super(action); decorate(); } 
		  public PolygonButtonLeft(Icon icon) { super(icon); decorate(); } 
		  public PolygonButtonLeft(String text, Icon icon) { super(text, icon); decorate(); } 
		  protected void decorate() { setBorderPainted(false); setOpaque(false); }
		  protected void drawString(Graphics g, String text, int x, int y) {
		        for (String line : text.split("\n"))
		            g.drawString(line, x, y += g.getFontMetrics().getHeight());
		    }
		  @Override 
		  protected void paintComponent(Graphics g) { 
			  // #1. 버튼 배경색 설정
			  Graphics2D graphics = (Graphics2D) g; 
			  graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON); 
			  if (getModel().isArmed()) {  // 마우스가 눌러진 상태
				  graphics.setColor(getBackground().darker());  
			  }else if (getModel().isRollover()) { // 마우스가 올려진 상태
				  graphics.setColor(getBackground().darker());
			  }else { // 평상시 
				  graphics.setColor(getBackground()); 
			  } 
			  
			  int []x = {0, 0, 170, 205};
			  int []y = {0, 200, 200, 0};
			  graphics.fillPolygon(x, y, 4); 

			  // #2. 버튼 이름 추가
			  graphics.setColor(getForeground()); 
			  graphics.setFont(getFont());
			  String text = getText();
			  int j = 20; // 버튼 글자 x좌표
			  int k = 25; // 버튼 글자 y좌표
			  drawString(g, text, j, k);
			  graphics.dispose(); 
			  super.paintComponent(g); 
			  
			  }
	}
	
	// 우측메뉴 버튼 클래스
	public class PolygonButtonRight extends JButton{
		public PolygonButtonRight() { super(); decorate(); } 
		  public PolygonButtonRight(String text) { super(text); decorate(); } 
		  public PolygonButtonRight(Action action) { super(action); decorate(); } 
		  public PolygonButtonRight(Icon icon) { super(icon); decorate(); } 
		  public PolygonButtonRight(String text, Icon icon) { super(text, icon); decorate(); } 
		  protected void decorate() { setBorderPainted(false); setOpaque(false); }
		  protected void drawString(Graphics g, String text, int x, int y) {
		        for (String line : text.split("\n"))
		            g.drawString(line, x, y += g.getFontMetrics().getHeight());
		    }
		  @Override 
		  protected void paintComponent(Graphics g) { 
			  // #1. 버튼 배경색 설정
			  Graphics2D graphics = (Graphics2D) g; 
			  graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON); 
			  if (getModel().isArmed()) {  // 마우스가 눌러진 상태
				  graphics.setColor(getBackground().darker());  
			  }else if (getModel().isRollover()) { // 마우스가 올려진 상태
				  graphics.setColor(getBackground().darker());
			  }else { // 평상시 
				  graphics.setColor(getBackground()); 
			  } 
			  
			  int []x = {35, 0, 225, 225};
			  int []y = {0, 200, 200, 0};
			  graphics.fillPolygon(x, y, 4); 

			  // #2. 버튼 이름 추가
			  graphics.setColor(getForeground()); 
			  graphics.setFont(getFont());
			  String text = getText();
			  int j = 40; // 버튼 글자 x좌표
			  int k = -5; // 버튼 글자 y좌표
			  drawString(g, text, j, k);
			  graphics.dispose(); 
			  super.paintComponent(g); 
			  
			  }
	}
	public static void main(String [] args) {
		new LearningManagement();
	}
}*/

package LearningPlanner;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import MainDisplay.*;
import LearningPlanner.CheckStudyPlan;
import LearningPlanner.SetStudyPlan;

public class LearningManagement extends JFrame {
	public LearningManagement() {
		// # 0. 기본 설정
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(null);

		// # 1. 폰트 설정
		Font headerFont = new Font("맑은 고딕", Font.BOLD, 20);
		Font contentFont = new Font("맑은 고딕", Font.BOLD, 25);
		Font menuFont = new Font("맑은 고딕", Font.BOLD, 45);

		// # 2. 상단 제목
		// # 2-1. 상단 제목
		JLabel headerTitle = new JLabel("학습 플래너");
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

		// # 3. 본문
		// # 3-1. 본문 제목
		JLabel contentTitle = new JLabel("나의 목표 관리");
		contentTitle.setLocation(120, 135);
		contentTitle.setSize(170, 25);
		contentTitle.setFont(contentFont);
		contentTitle.setForeground(Color.BLACK);
		c.add(contentTitle);

		// # 3-2. 본문 바
		barPanel contentBar = new barPanel();
		contentBar.setLayout(null);
		contentBar.setSize(300, 30);
		contentBar.setLocation(0, 150);
		c.add(contentBar);

		// # 4. 메뉴 버튼
		// # 4-1. 학습량 설정 버튼
		PolygonButtonLeft leftMenu = new PolygonButtonLeft("학습량\n 설정"); // 버튼 생성
		leftMenu.setBackground(new Color(112, 173, 71));
		leftMenu.setForeground(Color.WHITE);
		leftMenu.setFont(menuFont);
		leftMenu.setLocation(0, 200); // 버튼의 위치 설정
		leftMenu.setSize(220, 200); //
		c.add(leftMenu);

		// # 4-2. 목표 성취율 확인 버튼
		PolygonButtonRight rightMenu = new PolygonButtonRight("목표\n성취율\n확인"); // 버튼 생성
		rightMenu.setBackground(new Color(47, 85, 151));
		rightMenu.setForeground(Color.WHITE);
		rightMenu.setFont(menuFont);
		rightMenu.setLocation(180, 200); // 버튼의 위치 설정
		rightMenu.setSize(225, 200); //
		c.add(rightMenu);

		// # 6. 이벤트 추가하기
		// #6-1. Home 버튼 이벤트 추가
		homeButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. 메인페이지로 이동하기
				new MainDisplay();
				setVisible(false); // 해당 창 안보이기
			}
		});

		// #6-2. 왼쪽 메뉴 버튼 이벤트 추가
		leftMenu.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				SetStudyPlan set = new SetStudyPlan();
				set.SetStudyPlan();
				setVisible(false);
			}
		});

		// #6-3. 오른쪽 메뉴 버튼 이벤트 추가
		rightMenu.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CheckStudyPlan check = new CheckStudyPlan();
				check.CheckStudyPlan();
				setVisible(false);
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

	// 좌측메뉴 버튼 클래스
	public class PolygonButtonLeft extends JButton {
		public PolygonButtonLeft() {
			super();
			decorate();
		}

		public PolygonButtonLeft(String text) {
			super(text);
			decorate();
		}

		public PolygonButtonLeft(Action action) {
			super(action);
			decorate();
		}

		public PolygonButtonLeft(Icon icon) {
			super(icon);
			decorate();
		}

		public PolygonButtonLeft(String text, Icon icon) {
			super(text, icon);
			decorate();
		}

		protected void decorate() {
			setBorderPainted(false);
			setOpaque(false);
		}

		protected void drawString(Graphics g, String text, int x, int y) {
			for (String line : text.split("\n"))
				g.drawString(line, x, y += g.getFontMetrics().getHeight());
		}

		@Override
		protected void paintComponent(Graphics g) {
			// #1. 버튼 배경색 설정
			Graphics2D graphics = (Graphics2D) g;
			graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
			if (getModel().isArmed()) { // 마우스가 눌러진 상태
				graphics.setColor(getBackground().darker());
			} else if (getModel().isRollover()) { // 마우스가 올려진 상태
				graphics.setColor(getBackground().darker());
			} else { // 평상시
				graphics.setColor(getBackground());
			}

			int[] x = { 0, 0, 170, 205 };
			int[] y = { 0, 200, 200, 0 };
			graphics.fillPolygon(x, y, 4);

			// #2. 버튼 이름 추가
			graphics.setColor(getForeground());
			graphics.setFont(getFont());
			String text = getText();
			int j = 20; // 버튼 글자 x좌표
			int k = 25; // 버튼 글자 y좌표
			drawString(g, text, j, k);
			graphics.dispose();
			super.paintComponent(g);

		}
	}

	// 우측메뉴 버튼 클래스
	public class PolygonButtonRight extends JButton {
		public PolygonButtonRight() {
			super();
			decorate();
		}

		public PolygonButtonRight(String text) {
			super(text);
			decorate();
		}

		public PolygonButtonRight(Action action) {
			super(action);
			decorate();
		}

		public PolygonButtonRight(Icon icon) {
			super(icon);
			decorate();
		}

		public PolygonButtonRight(String text, Icon icon) {
			super(text, icon);
			decorate();
		}

		protected void decorate() {
			setBorderPainted(false);
			setOpaque(false);
		}

		protected void drawString(Graphics g, String text, int x, int y) {
			for (String line : text.split("\n"))
				g.drawString(line, x, y += g.getFontMetrics().getHeight());
		}

		@Override
		protected void paintComponent(Graphics g) {
			// #1. 버튼 배경색 설정
			Graphics2D graphics = (Graphics2D) g;
			graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
			if (getModel().isArmed()) { // 마우스가 눌러진 상태
				graphics.setColor(getBackground().darker());
			} else if (getModel().isRollover()) { // 마우스가 올려진 상태
				graphics.setColor(getBackground().darker());
			} else { // 평상시
				graphics.setColor(getBackground());
			}

			int[] x = { 35, 0, 225, 225 };
			int[] y = { 0, 200, 200, 0 };
			graphics.fillPolygon(x, y, 4);

			// #2. 버튼 이름 추가
			graphics.setColor(getForeground());
			graphics.setFont(getFont());
			String text = getText();
			int j = 40; // 버튼 글자 x좌표
			int k = -5; // 버튼 글자 y좌표
			drawString(g, text, j, k);
			graphics.dispose();
			super.paintComponent(g);

		}
	}

	public static void main(String[] args) {
		new LearningManagement();
	}
}
