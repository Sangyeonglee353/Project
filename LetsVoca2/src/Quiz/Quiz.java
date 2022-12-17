package Quiz;

import java.awt.image.BufferedImage;
import java.awt.*;
import javax.swing.*;
import java.io.File; /* 단어장 목록 읽어오기 */

import LearningPlanner.LearningManagement;
import LearningPlanner.LearningManagement.PolygonButtonLeft;
import LearningPlanner.LearningManagement.PolygonButtonRight;
import LearningPlanner.LearningManagement.barPanel;
import MainDisplay.MainDisplay;
import MainDisplay.MainDisplay.RoundedButton;
import VocaManagement.VocaListManagement;

import java.awt.event.*;

public class Quiz extends JFrame{
	
	// 버튼에 라운드 주기
	public class RoundedButton extends JButton {
	  public RoundedButton() { super(); decorate(); } 
	  public RoundedButton(String text) { super(text); decorate(); } 
	  public RoundedButton(Action action) { super(action); decorate(); } 
	  public RoundedButton(Icon icon) { super(icon); decorate(); } 
	  public RoundedButton(String text, Icon icon) { super(text, icon); decorate(); } 
	  protected void decorate() { setBorderPainted(false); setOpaque(false); }
	  
	  @Override 
	  protected void paintComponent(Graphics g) { 
		  int width = getWidth(); 
		  int height = getHeight(); 
		  Graphics2D graphics = (Graphics2D) g; 
		  graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON); 
		  if (getModel().isArmed()) {  // 마우스가 눌러진 상태
			  graphics.setColor(getBackground().darker());  
		  }else if (getModel().isRollover()) { // 마우스가 올려진 상태
			  graphics.setColor(getBackground().darker());
		  }else { // 평상시 
			  graphics.setColor(getBackground()); 
		  } 
		  
		  graphics.fillRoundRect(0, 0, width, height, 30, 30); 
		  
		  FontMetrics fontMetrics = graphics.getFontMetrics(); 
		  Rectangle stringBounds = fontMetrics.getStringBounds(this.getText(), graphics).getBounds(); 
		  int textX = (width - stringBounds.width) / 2;
		  //int textX = 50;
		  int textY = (height - stringBounds.height) / 2 + fontMetrics.getAscent();
		  
		  //Image img = iconToImage(this.getIcon()); // 아이콘 이미지 가져오기
		  graphics.setColor(getForeground()); 
		  graphics.setFont(getFont());
		  //graphics.drawImage(img, textX-40, textY-40, null); // 버튼 아이콘 위치 조정
		  graphics.drawString(getText(), textX, textY);   // 버튼 글자 위치 조정
		  graphics.dispose(); 
		  super.paintComponent(g); 
		  
		  }
	  }
	   
	public Quiz() {
		
	}
	
	public void vocaListDisplay(){
		
		setTitle("이젠 해!! VOCA");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		Container c = getContentPane(); // 컨텐트팬 알아내기
	
		setLayout(null); // 배치관리자 제거
		
		// #0. 폰트 설정
		Font menuFont = new Font("맑은 고딕", Font.BOLD, 15);
		
		// #1. 상단 로고 삽입
		ImageIcon topLogo = new ImageIcon("images/top_logo.png");
		JLabel imageLabel = new JLabel(topLogo);
		imageLabel.setSize(260, 50); // label 크기 설정
		imageLabel.setLocation(80, 50); // label 위치 설정
		
		// #2. 단어장 목록 삽입 -> 단어장 목록 완성시 단어장의 제목을 읽어와서 보여주기
		int vocaNum = 9; // 단어장 개수
		String [] vocaNameList = new String[vocaNum];
		
		// #2-1. 단어장 제목 가져오기
		File vocaFile = new File("voca");
		File[] subFiles = vocaFile.listFiles(); // 디렉토리에 포함된 파일과 디렉토리 이름의 리스트 얻기
		
		for (int i=0; i<subFiles.length; i++) { // subFiles 배열의 각 File에 대해 루프
			File f = subFiles[i];
			int dot = f.getName().lastIndexOf('.');
			if(dot > -1) {
			  //확장자 제거
			  vocaNameList[i] = f.getName().substring(0, dot);
			}
		}
		
		// #2-2. 화면에 단어장 GUI 보여주기
		RoundedButton [] vocaList = new RoundedButton[vocaNum];
		for(int i = 0; i < vocaNum; i++) {
			vocaList[i] = new RoundedButton(vocaNameList[i]); 
			vocaList[i].setFont(menuFont);
			vocaList[i].setForeground(new Color(255, 255, 255));
			vocaList[i].setBackground(new Color(97, 192, 191));
			vocaList[i].setSize(110, 110);
			c.add(vocaList[i]);
		}
		
		// #2.3 단어장 목록 위치 지정
		int x1 = 25;
		int y1 = 125;
		int y2 = y1+130;
		int y3 = y2+130;
		vocaList[0].setLocation(x1, y1);
		vocaList[1].setLocation(x1+125, y1);
		vocaList[2].setLocation(x1+250, y1);
		vocaList[3].setLocation(x1, y2);
		vocaList[4].setLocation(x1+125, y2);
		vocaList[5].setLocation(x1+250, y2);
		vocaList[6].setLocation(x1, y3);
		vocaList[7].setLocation(x1+125, y3);
		vocaList[8].setLocation(x1+250, y3);
		
		// #2.4 단어장 목록 이벤트 추가
		for(int i = 0; i< vocaNum; i++)
		{
			String vocaName = vocaNameList[i]; // 단어장 이름 저장
			vocaList[i].addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					// 퀴즈 유형 선택하기
					new quizChoice(vocaName);
					setVisible(false); // 창 안보이게 하기
				}
			});
		}
		
		
		// #3. 배치관리자에 추가
		c.add(imageLabel); // 배치관리자에 상단 로고 추가
		
		c.setBackground(Color.WHITE); // 배경색 흰색으로 설정
		
		// 전체 프레임 사이즈
		setSize(420, 550);
		setResizable(false); // 창의 크기를 변경하지 못하도록 설정
		setVisible(true);
		}
	
}

/* 퀴즈 유형 선택 클래스 */
class quizChoice extends JFrame{
	// 아이콘 -> 이미지로 변환
	public Image iconToImage(Icon icon) { 
 	   if (icon instanceof ImageIcon) {
 	      return ((ImageIcon)icon).getImage();
 	   } else {
 	      int width = icon.getIconWidth();
 	      int height = icon.getIconHeight();
 	      BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
 	      Graphics2D g2 = (Graphics2D) image.getGraphics();
 	      icon.paintIcon(null, g2, 0, 0);
 	      return image;
 	   }
 	}
	
   // 버튼에 라운드 주기
   public class RoundedButton extends JButton {
      public RoundedButton() { super(); decorate(); } 
      public RoundedButton(String text) { super(text); decorate(); } 
      public RoundedButton(Action action) { super(action); decorate(); } 
      public RoundedButton(Icon icon) { super(icon); decorate(); } 
      public RoundedButton(String text, Icon icon) { super(text, icon); decorate(); } 
      protected void decorate() { setBorderPainted(false); setOpaque(false); }
      
      @Override 
      protected void paintComponent(Graphics g) { 
    	  int width = getWidth(); 
    	  int height = getHeight(); 
    	  Graphics2D graphics = (Graphics2D) g; 
    	  graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON); 
    	  if (getModel().isArmed()) {  // 마우스가 눌러진 상태
    		  graphics.setColor(getBackground().darker());  
    	  }else if (getModel().isRollover()) { // 마우스가 올려진 상태
    		  graphics.setColor(getBackground().darker());
    	  }else { // 평상시 
    		  graphics.setColor(getBackground()); 
    	  } 
    	  
    	  graphics.fillRoundRect(0, 0, width, height, 25, 25); 
    	  
    	  FontMetrics fontMetrics = graphics.getFontMetrics(); 
    	  Rectangle stringBounds = fontMetrics.getStringBounds(this.getText(), graphics).getBounds(); 
    	  //int textX = (width - stringBounds.width) / 2;
    	  int textX = 50;
    	  int textY = (height - stringBounds.height) / 2 + fontMetrics.getAscent();
    	  
    	  Image img = iconToImage(this.getIcon()); // 아이콘 이미지 가져오기
    	  graphics.setColor(getForeground()); 
    	  graphics.setFont(getFont());
    	  graphics.drawImage(img, textX-40, textY-45, null); // 버튼 아이콘 위치 조정
    	  graphics.drawString(getText(), textX+30, textY);   // 버튼 글자 위치 조정
    	  graphics.dispose(); 
    	  super.paintComponent(g); 
    	  
    	  }
      }
		
	public quizChoice(String vocaName) {	
		setTitle("이젠 해!! VOCA");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		Container c = getContentPane(); // 컨텐트팬 알아내기
	
		setLayout(null); // 배치관리자 제거
		
		// #0. 폰트 설정
		Font menuFont = new Font("맑은 고딕", Font.BOLD, 30);
		
		// #1. 상단 로고 삽입
		ImageIcon topLogo = new ImageIcon("images/top_logo.png");
		JLabel imageLabel = new JLabel(topLogo);
		imageLabel.setSize(260, 50); // label 크기 설정
		imageLabel.setLocation(80, 50); // label 위치 설정
		
		// #2. 선택 메뉴 삽입
		// #2.1 상단 버튼
		ImageIcon menuOneIcon = new ImageIcon("images/Multi_Quiz.png");
		RoundedButton buttonOne = new RoundedButton("객관식 퀴즈", menuOneIcon);
		buttonOne.setSize(360, 100);
		buttonOne.setLocation(20, 125);
		buttonOne.setBackground(new Color(255, 182, 185));
		buttonOne.setFont(menuFont);
		buttonOne.setForeground(new Color(255, 255, 255));
		
		// #2.2 중단 버튼
		ImageIcon menuTwoIcon = new ImageIcon("images/Short_Quiz.png");
		RoundedButton buttonTwo = new RoundedButton("주관식 퀴즈", menuTwoIcon);
		buttonTwo.setSize(360, 100);
		buttonTwo.setLocation(20, 250);
		buttonTwo.setBackground(new Color(250, 227, 217));
		buttonTwo.setFont(menuFont);
		buttonTwo.setForeground(new Color(255, 255, 255));
		
		// #2.3 하단 버튼
		ImageIcon menuThreeIcon = new ImageIcon("images/Image_Quiz.png");
		RoundedButton buttonThree = new RoundedButton("이미지 퀴즈", menuThreeIcon);
		buttonThree.setSize(360, 100);
		buttonThree.setLocation(20, 375);
		buttonThree.setBackground(new Color(187, 232, 214));
		buttonThree.setFont(menuFont);
		buttonThree.setForeground(new Color(255, 255, 255));
		
		// #3. 배치관리자에 추가
		c.add(imageLabel); // 배치관리자에 상단 로고 추가
		c.add(buttonOne); // 배치관리자에 첫번째 버튼 추가
		c.add(buttonTwo); // 배치관리자에 두번째 버튼 추가
		c.add(buttonThree); // 배치관리자에 세번째 버튼 추가
		
		// #4. 이벤츠 추가
		// #4-1. 상단 버튼 이벤트 추가
		buttonOne.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. 객관식 퀴즈 불러오기
				final int quizType = 0;
				new langChoice(quizType, vocaName);
				//new MultipleChoiceQuiz();
				setVisible(false); // 해당 창 안보이기
			}
		});
		
		// #4-2. 중단 버튼 이벤트 추가
		buttonTwo.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 2. 주관식 퀴즈 불러오기
				final int quizType = 1;
				new langChoice(quizType, vocaName);
				//new ShortAnswerQuiz();
				setVisible(false);
			}
		});
		
		// #4-3. 하단 버튼 이벤트 추가
		buttonThree.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 3. 이미지 퀴즈 불러오기
				new ImageQuiz(vocaName);
				setVisible(false);
			}
		});
				
		c.setBackground(Color.WHITE); // 배경색 흰색으로 설정
		setSize(420, 550); // 전체 프레임 사이즈
		setResizable(false); // 창의 크기를 변경하지 못하도록 설정
		setVisible(true);
	}
}

// #3. 보기 언어 선택
class langChoice extends JFrame {
	private int quizType; // 퀴즈 타입 저장용
	private String vocaName; // 단어장 이름 저장용
	public langChoice() {}
	public langChoice(int quizType, String vocaName) {
		// 이전 메뉴에서 가져온 퀴즈타입 저장
		this.quizType = quizType; 
		this.vocaName = vocaName;
		
		// # 0. 기본 설정
		setTitle("이젠 해!! VOCA");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane(); // 컨텐트팬 알아내기
		setLayout(null); // 배치관리자 제거
		
		// # 1. 폰트 설정
		Font headerFont = new Font("맑은 고딕", Font.BOLD, 20);
		Font contentFont = new Font("맑은 고딕", Font.BOLD, 25);
		Font menuFont = new Font("맑은 고딕", Font.BOLD, 50);
		
		// # 2. 상단 로고 삽입
		ImageIcon topLogo = new ImageIcon("images/top_logo.png");
		JLabel imageLabel = new JLabel(topLogo);
		imageLabel.setSize(260, 50); // label 크기 설정
		imageLabel.setLocation(80, 50); // label 위치 설정
		
		// # 3. 본문
		// # 3-1. 본문 제목
		String menuText = "";
		if(quizType == 0) {
			menuText = "객관식 보기 선택";
		}
		else {
			menuText = "주관식 보기 선택";
		}
		JLabel contentTitle = new JLabel(menuText);
		contentTitle.setLocation(110, 135);
		contentTitle.setSize(200,25);
		contentTitle.setFont(contentFont);
		contentTitle.setForeground(Color.BLACK);
		
		// # 3-2. 본문 바
		barPanel contentBar = new barPanel();
		contentBar.setLayout(null);
		contentBar.setSize(300, 30);
		contentBar.setLocation(0, 150);
		contentBar.setBackground(Color.WHITE);
		
		// # 4. 메뉴 버튼 
		// # 4-1. 영어 버튼
		PolygonButtonLeft leftMenu = new PolygonButtonLeft("English\n (영어)"); // 버튼 생성
		leftMenu.setBackground(new Color(112,173,71));
		leftMenu.setForeground(Color.WHITE);
		leftMenu.setFont(menuFont);
		leftMenu.setLocation(0, 200); // 버튼의 위치 설정
		leftMenu.setSize(220, 200); // 
		
		// # 4-2. 한글 버튼
		PolygonButtonRight rightMenu = new PolygonButtonRight("한글"); // 버튼 생성
		rightMenu.setBackground(new Color(47,85,151));
		rightMenu.setForeground(Color.WHITE);
		rightMenu.setFont(menuFont);
		rightMenu.setLocation(180, 200); // 버튼의 위치 설정
		rightMenu.setSize(225, 200); // 
		
		// # 5. 컨텐트팬에 버튼 추가
		c.add(imageLabel);
		c.add(contentTitle);
		c.add(contentBar);
		c.add(leftMenu);
		c.add(rightMenu);
		
		// # 6. 이벤트 추가
		// # 6-1. 좌측 버튼 이벤트 추가
		leftMenu.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if(quizType == 0) {
					// 1. 객관식 퀴즈 불러오기
					new MultipleChoiceQuiz(vocaName);
				}
				else {
					// 2. 주관식 퀴즈 불러오기
					new ShortAnswerQuiz(vocaName);
				}
				setVisible(false); // 해당 창 안보이기
			}
		});
		
		// # 6-2. 우측 버튼 이벤트 추가
		rightMenu.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if(quizType == 0) {
					// 1. 객관식 퀴즈 불러오기
					new MultipleChoiceQuiz(vocaName);
				}
				else {
					// 2. 주관식 퀴즈 불러오기
					new ShortAnswerQuiz(vocaName);
				}
				setVisible(false); // 해당 창 안보이기
			}
		});		
		
		c.setBackground(Color.WHITE); // 배경색 설정
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
			  int j = 10; // 버튼 글자 x좌표
			  int k = -5; // 버튼 글자 y좌표
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
			  int j = 60; // 버튼 글자 x좌표
			  int k = 110; // 버튼 글자 y좌표
			  drawString(g, text, j, k);
			  graphics.dispose(); 
			  super.paintComponent(g); 
			  
			  }
	}
}