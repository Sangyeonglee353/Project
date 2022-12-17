package MainDisplay;
import Quiz.*;
import VocaManagement.*;
import LearningPlanner.*;
import java.awt.image.BufferedImage;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class MainDisplay extends JFrame{	
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
    	  graphics.drawImage(img, textX-40, textY-40, null); // 버튼 아이콘 위치 조정
    	  graphics.drawString(getText(), textX+20, textY);   // 버튼 글자 위치 조정
    	  graphics.dispose(); 
    	  super.paintComponent(g); 
    	  
    	  }
      }
   
	public MainDisplay() {
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
		ImageIcon menuOneIcon = new ImageIcon("images/main_menu1.png");
		RoundedButton buttonOne = new RoundedButton("단어 퀴즈 시작하기", menuOneIcon);
		buttonOne.setSize(360, 100);
		buttonOne.setLocation(20, 125);
		buttonOne.setBackground(new Color(255, 182, 185));
		buttonOne.setFont(menuFont);
		buttonOne.setForeground(new Color(255, 255, 255));
		
		// #2.2 중단 버튼
		ImageIcon menuTwoIcon = new ImageIcon("images/main_menu2.png");
		RoundedButton buttonTwo = new RoundedButton("나만의 단어장", menuTwoIcon);
		buttonTwo.setSize(360, 100);
		buttonTwo.setLocation(20, 250);
		buttonTwo.setBackground(new Color(250, 227, 217));
		buttonTwo.setFont(menuFont);
		buttonTwo.setForeground(new Color(255, 255, 255));
		
		// #2.3 하단 버튼
		ImageIcon menuThreeIcon = new ImageIcon("images/main_menu3.png");
		RoundedButton buttonThree = new RoundedButton("학습 플래너", menuThreeIcon);
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
		
		// #4. 이벤트 추가하기
		// #4-1. 상단 버튼 이벤트 추가
		buttonOne.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. 단어장 목록 불러오기
				Quiz selectQuiz = new Quiz();
				selectQuiz.vocaListDisplay();
				setVisible(false); // 해당 창 안보이기
				// 버튼별 안보이기
				/*
				buttonOne.setVisible(false); // 창 안보이게 하기
				buttonTwo.setVisible(false); // 창 안보이게 하기
				buttonThree.setVisible(false); // 창 안보이게 하기
				*/
			}
		});
		
		// #4-2. 중단 버튼 이벤트 추가
		buttonTwo.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 2. 단어장 관리 불러오기
				VocaListManagement vocaMgt = new VocaListManagement();
				setVisible(false);
			}
		});
		
		// #4-3. 하단 버튼 이벤트 추가
		buttonThree.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 3. 학습 플래너 불러오기
				LearningManagement learnMgt = new LearningManagement();
				setVisible(false);
			}
		});
		
		c.setBackground(Color.WHITE); // 배경색 흰색으로 설정
		//setIconImage(topLogo.getImage()); // 상단바 아이콘 변경
		
		// 전체 프레임 사이즈
		setSize(420, 550);
		setResizable(false); // 창의 크기를 변경하지 못하도록 설정
		setVisible(true);
	}
	public static void main(String[] args) {
		new MainDisplay();
	}
}