package Quiz;

import java.awt.image.BufferedImage;
import java.awt.*;
import javax.swing.*;
import java.io.File; /* �ܾ��� ��� �о���� */

import LearningPlanner.LearningManagement;
import LearningPlanner.LearningManagement.PolygonButtonLeft;
import LearningPlanner.LearningManagement.PolygonButtonRight;
import LearningPlanner.LearningManagement.barPanel;
import MainDisplay.MainDisplay;
import MainDisplay.MainDisplay.RoundedButton;
import VocaManagement.VocaListManagement;

import java.awt.event.*;

public class Quiz extends JFrame{
	
	// ��ư�� ���� �ֱ�
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
		  if (getModel().isArmed()) {  // ���콺�� ������ ����
			  graphics.setColor(getBackground().darker());  
		  }else if (getModel().isRollover()) { // ���콺�� �÷��� ����
			  graphics.setColor(getBackground().darker());
		  }else { // ���� 
			  graphics.setColor(getBackground()); 
		  } 
		  
		  graphics.fillRoundRect(0, 0, width, height, 30, 30); 
		  
		  FontMetrics fontMetrics = graphics.getFontMetrics(); 
		  Rectangle stringBounds = fontMetrics.getStringBounds(this.getText(), graphics).getBounds(); 
		  int textX = (width - stringBounds.width) / 2;
		  //int textX = 50;
		  int textY = (height - stringBounds.height) / 2 + fontMetrics.getAscent();
		  
		  //Image img = iconToImage(this.getIcon()); // ������ �̹��� ��������
		  graphics.setColor(getForeground()); 
		  graphics.setFont(getFont());
		  //graphics.drawImage(img, textX-40, textY-40, null); // ��ư ������ ��ġ ����
		  graphics.drawString(getText(), textX, textY);   // ��ư ���� ��ġ ����
		  graphics.dispose(); 
		  super.paintComponent(g); 
		  
		  }
	  }
	   
	public Quiz() {
		
	}
	
	public void vocaListDisplay(){
		
		setTitle("���� ��!! VOCA");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		Container c = getContentPane(); // ����Ʈ�� �˾Ƴ���
	
		setLayout(null); // ��ġ������ ����
		
		// #0. ��Ʈ ����
		Font menuFont = new Font("���� ���", Font.BOLD, 15);
		
		// #1. ��� �ΰ� ����
		ImageIcon topLogo = new ImageIcon("images/top_logo.png");
		JLabel imageLabel = new JLabel(topLogo);
		imageLabel.setSize(260, 50); // label ũ�� ����
		imageLabel.setLocation(80, 50); // label ��ġ ����
		
		// #2. �ܾ��� ��� ���� -> �ܾ��� ��� �ϼ��� �ܾ����� ������ �о�ͼ� �����ֱ�
		int vocaNum = 9; // �ܾ��� ����
		String [] vocaNameList = new String[vocaNum];
		
		// #2-1. �ܾ��� ���� ��������
		File vocaFile = new File("voca");
		File[] subFiles = vocaFile.listFiles(); // ���丮�� ���Ե� ���ϰ� ���丮 �̸��� ����Ʈ ���
		
		for (int i=0; i<subFiles.length; i++) { // subFiles �迭�� �� File�� ���� ����
			File f = subFiles[i];
			int dot = f.getName().lastIndexOf('.');
			if(dot > -1) {
			  //Ȯ���� ����
			  vocaNameList[i] = f.getName().substring(0, dot);
			}
		}
		
		// #2-2. ȭ�鿡 �ܾ��� GUI �����ֱ�
		RoundedButton [] vocaList = new RoundedButton[vocaNum];
		for(int i = 0; i < vocaNum; i++) {
			vocaList[i] = new RoundedButton(vocaNameList[i]); 
			vocaList[i].setFont(menuFont);
			vocaList[i].setForeground(new Color(255, 255, 255));
			vocaList[i].setBackground(new Color(97, 192, 191));
			vocaList[i].setSize(110, 110);
			c.add(vocaList[i]);
		}
		
		// #2.3 �ܾ��� ��� ��ġ ����
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
		
		// #2.4 �ܾ��� ��� �̺�Ʈ �߰�
		for(int i = 0; i< vocaNum; i++)
		{
			String vocaName = vocaNameList[i]; // �ܾ��� �̸� ����
			vocaList[i].addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					// ���� ���� �����ϱ�
					new quizChoice(vocaName);
					setVisible(false); // â �Ⱥ��̰� �ϱ�
				}
			});
		}
		
		
		// #3. ��ġ�����ڿ� �߰�
		c.add(imageLabel); // ��ġ�����ڿ� ��� �ΰ� �߰�
		
		c.setBackground(Color.WHITE); // ���� ������� ����
		
		// ��ü ������ ������
		setSize(420, 550);
		setResizable(false); // â�� ũ�⸦ �������� ���ϵ��� ����
		setVisible(true);
		}
	
}

/* ���� ���� ���� Ŭ���� */
class quizChoice extends JFrame{
	// ������ -> �̹����� ��ȯ
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
	
   // ��ư�� ���� �ֱ�
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
    	  if (getModel().isArmed()) {  // ���콺�� ������ ����
    		  graphics.setColor(getBackground().darker());  
    	  }else if (getModel().isRollover()) { // ���콺�� �÷��� ����
    		  graphics.setColor(getBackground().darker());
    	  }else { // ���� 
    		  graphics.setColor(getBackground()); 
    	  } 
    	  
    	  graphics.fillRoundRect(0, 0, width, height, 25, 25); 
    	  
    	  FontMetrics fontMetrics = graphics.getFontMetrics(); 
    	  Rectangle stringBounds = fontMetrics.getStringBounds(this.getText(), graphics).getBounds(); 
    	  //int textX = (width - stringBounds.width) / 2;
    	  int textX = 50;
    	  int textY = (height - stringBounds.height) / 2 + fontMetrics.getAscent();
    	  
    	  Image img = iconToImage(this.getIcon()); // ������ �̹��� ��������
    	  graphics.setColor(getForeground()); 
    	  graphics.setFont(getFont());
    	  graphics.drawImage(img, textX-40, textY-45, null); // ��ư ������ ��ġ ����
    	  graphics.drawString(getText(), textX+30, textY);   // ��ư ���� ��ġ ����
    	  graphics.dispose(); 
    	  super.paintComponent(g); 
    	  
    	  }
      }
		
	public quizChoice(String vocaName) {	
		setTitle("���� ��!! VOCA");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		Container c = getContentPane(); // ����Ʈ�� �˾Ƴ���
	
		setLayout(null); // ��ġ������ ����
		
		// #0. ��Ʈ ����
		Font menuFont = new Font("���� ���", Font.BOLD, 30);
		
		// #1. ��� �ΰ� ����
		ImageIcon topLogo = new ImageIcon("images/top_logo.png");
		JLabel imageLabel = new JLabel(topLogo);
		imageLabel.setSize(260, 50); // label ũ�� ����
		imageLabel.setLocation(80, 50); // label ��ġ ����
		
		// #2. ���� �޴� ����
		// #2.1 ��� ��ư
		ImageIcon menuOneIcon = new ImageIcon("images/Multi_Quiz.png");
		RoundedButton buttonOne = new RoundedButton("������ ����", menuOneIcon);
		buttonOne.setSize(360, 100);
		buttonOne.setLocation(20, 125);
		buttonOne.setBackground(new Color(255, 182, 185));
		buttonOne.setFont(menuFont);
		buttonOne.setForeground(new Color(255, 255, 255));
		
		// #2.2 �ߴ� ��ư
		ImageIcon menuTwoIcon = new ImageIcon("images/Short_Quiz.png");
		RoundedButton buttonTwo = new RoundedButton("�ְ��� ����", menuTwoIcon);
		buttonTwo.setSize(360, 100);
		buttonTwo.setLocation(20, 250);
		buttonTwo.setBackground(new Color(250, 227, 217));
		buttonTwo.setFont(menuFont);
		buttonTwo.setForeground(new Color(255, 255, 255));
		
		// #2.3 �ϴ� ��ư
		ImageIcon menuThreeIcon = new ImageIcon("images/Image_Quiz.png");
		RoundedButton buttonThree = new RoundedButton("�̹��� ����", menuThreeIcon);
		buttonThree.setSize(360, 100);
		buttonThree.setLocation(20, 375);
		buttonThree.setBackground(new Color(187, 232, 214));
		buttonThree.setFont(menuFont);
		buttonThree.setForeground(new Color(255, 255, 255));
		
		// #3. ��ġ�����ڿ� �߰�
		c.add(imageLabel); // ��ġ�����ڿ� ��� �ΰ� �߰�
		c.add(buttonOne); // ��ġ�����ڿ� ù��° ��ư �߰�
		c.add(buttonTwo); // ��ġ�����ڿ� �ι�° ��ư �߰�
		c.add(buttonThree); // ��ġ�����ڿ� ����° ��ư �߰�
		
		// #4. �̺��� �߰�
		// #4-1. ��� ��ư �̺�Ʈ �߰�
		buttonOne.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. ������ ���� �ҷ�����
				final int quizType = 0;
				new langChoice(quizType, vocaName);
				//new MultipleChoiceQuiz();
				setVisible(false); // �ش� â �Ⱥ��̱�
			}
		});
		
		// #4-2. �ߴ� ��ư �̺�Ʈ �߰�
		buttonTwo.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 2. �ְ��� ���� �ҷ�����
				final int quizType = 1;
				new langChoice(quizType, vocaName);
				//new ShortAnswerQuiz();
				setVisible(false);
			}
		});
		
		// #4-3. �ϴ� ��ư �̺�Ʈ �߰�
		buttonThree.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 3. �̹��� ���� �ҷ�����
				new ImageQuiz(vocaName);
				setVisible(false);
			}
		});
				
		c.setBackground(Color.WHITE); // ���� ������� ����
		setSize(420, 550); // ��ü ������ ������
		setResizable(false); // â�� ũ�⸦ �������� ���ϵ��� ����
		setVisible(true);
	}
}

// #3. ���� ��� ����
class langChoice extends JFrame {
	private int quizType; // ���� Ÿ�� �����
	private String vocaName; // �ܾ��� �̸� �����
	public langChoice() {}
	public langChoice(int quizType, String vocaName) {
		// ���� �޴����� ������ ����Ÿ�� ����
		this.quizType = quizType; 
		this.vocaName = vocaName;
		
		// # 0. �⺻ ����
		setTitle("���� ��!! VOCA");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane(); // ����Ʈ�� �˾Ƴ���
		setLayout(null); // ��ġ������ ����
		
		// # 1. ��Ʈ ����
		Font headerFont = new Font("���� ���", Font.BOLD, 20);
		Font contentFont = new Font("���� ���", Font.BOLD, 25);
		Font menuFont = new Font("���� ���", Font.BOLD, 50);
		
		// # 2. ��� �ΰ� ����
		ImageIcon topLogo = new ImageIcon("images/top_logo.png");
		JLabel imageLabel = new JLabel(topLogo);
		imageLabel.setSize(260, 50); // label ũ�� ����
		imageLabel.setLocation(80, 50); // label ��ġ ����
		
		// # 3. ����
		// # 3-1. ���� ����
		String menuText = "";
		if(quizType == 0) {
			menuText = "������ ���� ����";
		}
		else {
			menuText = "�ְ��� ���� ����";
		}
		JLabel contentTitle = new JLabel(menuText);
		contentTitle.setLocation(110, 135);
		contentTitle.setSize(200,25);
		contentTitle.setFont(contentFont);
		contentTitle.setForeground(Color.BLACK);
		
		// # 3-2. ���� ��
		barPanel contentBar = new barPanel();
		contentBar.setLayout(null);
		contentBar.setSize(300, 30);
		contentBar.setLocation(0, 150);
		contentBar.setBackground(Color.WHITE);
		
		// # 4. �޴� ��ư 
		// # 4-1. ���� ��ư
		PolygonButtonLeft leftMenu = new PolygonButtonLeft("English\n (����)"); // ��ư ����
		leftMenu.setBackground(new Color(112,173,71));
		leftMenu.setForeground(Color.WHITE);
		leftMenu.setFont(menuFont);
		leftMenu.setLocation(0, 200); // ��ư�� ��ġ ����
		leftMenu.setSize(220, 200); // 
		
		// # 4-2. �ѱ� ��ư
		PolygonButtonRight rightMenu = new PolygonButtonRight("�ѱ�"); // ��ư ����
		rightMenu.setBackground(new Color(47,85,151));
		rightMenu.setForeground(Color.WHITE);
		rightMenu.setFont(menuFont);
		rightMenu.setLocation(180, 200); // ��ư�� ��ġ ����
		rightMenu.setSize(225, 200); // 
		
		// # 5. ����Ʈ�ҿ� ��ư �߰�
		c.add(imageLabel);
		c.add(contentTitle);
		c.add(contentBar);
		c.add(leftMenu);
		c.add(rightMenu);
		
		// # 6. �̺�Ʈ �߰�
		// # 6-1. ���� ��ư �̺�Ʈ �߰�
		leftMenu.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if(quizType == 0) {
					// 1. ������ ���� �ҷ�����
					new MultipleChoiceQuiz(vocaName);
				}
				else {
					// 2. �ְ��� ���� �ҷ�����
					new ShortAnswerQuiz(vocaName);
				}
				setVisible(false); // �ش� â �Ⱥ��̱�
			}
		});
		
		// # 6-2. ���� ��ư �̺�Ʈ �߰�
		rightMenu.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if(quizType == 0) {
					// 1. ������ ���� �ҷ�����
					new MultipleChoiceQuiz(vocaName);
				}
				else {
					// 2. �ְ��� ���� �ҷ�����
					new ShortAnswerQuiz(vocaName);
				}
				setVisible(false); // �ش� â �Ⱥ��̱�
			}
		});		
		
		c.setBackground(Color.WHITE); // ���� ����
		setSize(420, 550); // ������ ũ��
		setResizable(false); // â�� ũ�⸦ �������� ���ϵ��� ����
		setVisible(true); // ������ ȭ�� ���
	}
	
	// �޴��� Ŭ����
	public class barPanel extends JPanel{
		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			g.setColor(Color.GRAY);
			g.fillRect(110, 20, 310, 3);
		}
	}
	// �����޴� ��ư Ŭ����
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
			  // #1. ��ư ���� ����
			  Graphics2D graphics = (Graphics2D) g; 
			  graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON); 
			  if (getModel().isArmed()) {  // ���콺�� ������ ����
				  graphics.setColor(getBackground().darker());  
			  }else if (getModel().isRollover()) { // ���콺�� �÷��� ����
				  graphics.setColor(getBackground().darker());
			  }else { // ���� 
				  graphics.setColor(getBackground()); 
			  } 
			  
			  int []x = {0, 0, 170, 205};
			  int []y = {0, 200, 200, 0};
			  graphics.fillPolygon(x, y, 4); 

			  // #2. ��ư �̸� �߰�
			  graphics.setColor(getForeground()); 
			  graphics.setFont(getFont());
			  String text = getText();
			  int j = 10; // ��ư ���� x��ǥ
			  int k = -5; // ��ư ���� y��ǥ
			  drawString(g, text, j, k);
			  graphics.dispose(); 
			  super.paintComponent(g); 
			  
			  }
	}
	
	// �����޴� ��ư Ŭ����
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
			  // #1. ��ư ���� ����
			  Graphics2D graphics = (Graphics2D) g; 
			  graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON); 
			  if (getModel().isArmed()) {  // ���콺�� ������ ����
				  graphics.setColor(getBackground().darker());  
			  }else if (getModel().isRollover()) { // ���콺�� �÷��� ����
				  graphics.setColor(getBackground().darker());
			  }else { // ���� 
				  graphics.setColor(getBackground()); 
			  } 
			  
			  int []x = {35, 0, 225, 225};
			  int []y = {0, 200, 200, 0};
			  graphics.fillPolygon(x, y, 4); 

			  // #2. ��ư �̸� �߰�
			  graphics.setColor(getForeground()); 
			  graphics.setFont(getFont());
			  String text = getText();
			  int j = 60; // ��ư ���� x��ǥ
			  int k = 110; // ��ư ���� y��ǥ
			  drawString(g, text, j, k);
			  graphics.dispose(); 
			  super.paintComponent(g); 
			  
			  }
	}
}