package MainDisplay;
import Quiz.*;
import VocaManagement.*;
import LearningPlanner.*;
import java.awt.image.BufferedImage;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class MainDisplay extends JFrame{	
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
    	  graphics.drawImage(img, textX-40, textY-40, null); // ��ư ������ ��ġ ����
    	  graphics.drawString(getText(), textX+20, textY);   // ��ư ���� ��ġ ����
    	  graphics.dispose(); 
    	  super.paintComponent(g); 
    	  
    	  }
      }
   
	public MainDisplay() {
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
		ImageIcon menuOneIcon = new ImageIcon("images/main_menu1.png");
		RoundedButton buttonOne = new RoundedButton("�ܾ� ���� �����ϱ�", menuOneIcon);
		buttonOne.setSize(360, 100);
		buttonOne.setLocation(20, 125);
		buttonOne.setBackground(new Color(255, 182, 185));
		buttonOne.setFont(menuFont);
		buttonOne.setForeground(new Color(255, 255, 255));
		
		// #2.2 �ߴ� ��ư
		ImageIcon menuTwoIcon = new ImageIcon("images/main_menu2.png");
		RoundedButton buttonTwo = new RoundedButton("������ �ܾ���", menuTwoIcon);
		buttonTwo.setSize(360, 100);
		buttonTwo.setLocation(20, 250);
		buttonTwo.setBackground(new Color(250, 227, 217));
		buttonTwo.setFont(menuFont);
		buttonTwo.setForeground(new Color(255, 255, 255));
		
		// #2.3 �ϴ� ��ư
		ImageIcon menuThreeIcon = new ImageIcon("images/main_menu3.png");
		RoundedButton buttonThree = new RoundedButton("�н� �÷���", menuThreeIcon);
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
		
		// #4. �̺�Ʈ �߰��ϱ�
		// #4-1. ��� ��ư �̺�Ʈ �߰�
		buttonOne.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. �ܾ��� ��� �ҷ�����
				Quiz selectQuiz = new Quiz();
				selectQuiz.vocaListDisplay();
				setVisible(false); // �ش� â �Ⱥ��̱�
				// ��ư�� �Ⱥ��̱�
				/*
				buttonOne.setVisible(false); // â �Ⱥ��̰� �ϱ�
				buttonTwo.setVisible(false); // â �Ⱥ��̰� �ϱ�
				buttonThree.setVisible(false); // â �Ⱥ��̰� �ϱ�
				*/
			}
		});
		
		// #4-2. �ߴ� ��ư �̺�Ʈ �߰�
		buttonTwo.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 2. �ܾ��� ���� �ҷ�����
				VocaListManagement vocaMgt = new VocaListManagement();
				setVisible(false);
			}
		});
		
		// #4-3. �ϴ� ��ư �̺�Ʈ �߰�
		buttonThree.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 3. �н� �÷��� �ҷ�����
				LearningManagement learnMgt = new LearningManagement();
				setVisible(false);
			}
		});
		
		c.setBackground(Color.WHITE); // ���� ������� ����
		//setIconImage(topLogo.getImage()); // ��ܹ� ������ ����
		
		// ��ü ������ ������
		setSize(420, 550);
		setResizable(false); // â�� ũ�⸦ �������� ���ϵ��� ����
		setVisible(true);
	}
	public static void main(String[] args) {
		new MainDisplay();
	}
}