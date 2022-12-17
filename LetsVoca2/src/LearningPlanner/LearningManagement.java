/*package LearningPlanner;

import javax.swing.*;
import MainDisplay.*;
import java.awt.*;
import java.awt.event.*;

public class LearningManagement extends JFrame {
	public LearningManagement() {
		// # 0. �⺻ ����
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(null);
		
		// # 1. ��Ʈ ����
		Font headerFont = new Font("���� ���", Font.BOLD, 20);
		Font contentFont = new Font("���� ���", Font.BOLD, 25);
		Font menuFont = new Font("���� ���", Font.BOLD, 45);
		
		// # 2. ��� ����
		// # 2-1. ��� ������ �г�
		// ������ �г�(Ȩ ��ư, ���� Ǭ �� ����)
		JPanel header = new JPanel();
		header.setLocation(0,0);
		header.setSize(420,50);
		header.setBackground(Color.BLACK);

		// # 2-2. ��� ����
		JLabel headerTitle = new JLabel("�н� �÷���");
		headerTitle.setLocation(145, -25);
		headerTitle.setSize(130,100);
		headerTitle.setFont(headerFont);
		headerTitle.setForeground(Color.WHITE);
		c.add(headerTitle);
		
		// # 2-3. Home ��ư
		JButton homeButton = new JButton(new ImageIcon("Images/home.png"));
		homeButton.setLocation(10,5);
		homeButton.setBackground(Color.BLACK);
		homeButton.setSize(42,42);
		homeButton.setBorderPainted(false);
		homeButton.setFocusPainted(false);
		
		// Home ��ư �̺�Ʈ �߰�
		homeButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. ������������ �̵��ϱ�
				new MainDisplay();
				setVisible(false); // �ش� â �Ⱥ��̱�
			}
		});
		
		// # 3. ����
		// # 3-1. ���� ����
		JLabel contentTitle = new JLabel("���� ��ǥ ����");
		contentTitle.setLocation(120, 135);
		contentTitle.setSize(170,25);
		contentTitle.setFont(contentFont);
		contentTitle.setForeground(Color.BLACK);
		
		// # 3-2. ���� ��
		barPanel contentBar = new barPanel();
		contentBar.setLayout(null);
		contentBar.setSize(300, 30);
		contentBar.setLocation(0, 150);
		
		// # 4. �޴� ��ư 
		// # 4-1. �н��� ���� ��ư
		PolygonButtonLeft leftMenu = new PolygonButtonLeft("�н���\n ����"); // ��ư ����
		leftMenu.setBackground(new Color(112,173,71));
		leftMenu.setForeground(Color.WHITE);
		leftMenu.setFont(menuFont);
		leftMenu.setLocation(0, 200); // ��ư�� ��ġ ����
		leftMenu.setSize(220, 200); // 
		
		// # 4-2. ��ǥ ������ Ȯ�� ��ư
		PolygonButtonRight rightMenu = new PolygonButtonRight("��ǥ\n������\nȮ��"); // ��ư ����
		rightMenu.setBackground(new Color(47,85,151));
		rightMenu.setForeground(Color.WHITE);
		rightMenu.setFont(menuFont);
		rightMenu.setLocation(180, 200); // ��ư�� ��ġ ����
		rightMenu.setSize(225, 200); // 
		
		// # 5. ����Ʈ�ҿ� ��ư �߰�
		c.add(header);
		c.add(homeButton);
		c.add(contentTitle);
		c.add(contentBar);
		c.add(leftMenu);
		c.add(rightMenu);
		
		setTitle("���� ��!! VOCA");
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
			  int j = 20; // ��ư ���� x��ǥ
			  int k = 25; // ��ư ���� y��ǥ
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
			  int j = 40; // ��ư ���� x��ǥ
			  int k = -5; // ��ư ���� y��ǥ
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
		// # 0. �⺻ ����
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(null);

		// # 1. ��Ʈ ����
		Font headerFont = new Font("���� ���", Font.BOLD, 20);
		Font contentFont = new Font("���� ���", Font.BOLD, 25);
		Font menuFont = new Font("���� ���", Font.BOLD, 45);

		// # 2. ��� ����
		// # 2-1. ��� ����
		JLabel headerTitle = new JLabel("�н� �÷���");
		headerTitle.setLocation(145, -25);
		headerTitle.setSize(130, 100);
		headerTitle.setFont(headerFont);
		headerTitle.setForeground(Color.WHITE);
		c.add(headerTitle);
		
		// # 2-2. ��� ������ �г�
		// ������ �г�(Ȩ ��ư, ���� Ǭ �� ����)
		JPanel header = new JPanel();
		header.setLocation(0, 0);
		header.setSize(420, 50);
		header.setBackground(Color.BLACK);
		c.add(header);

		// # 2-3. Home ��ư
		JButton homeButton = new JButton(new ImageIcon("Images/home.png"));
		homeButton.setLocation(10, 5);
		homeButton.setBackground(Color.BLACK);
		homeButton.setSize(42, 42);
		homeButton.setBorderPainted(false);
		homeButton.setFocusPainted(false);
		c.add(homeButton);

		// # 3. ����
		// # 3-1. ���� ����
		JLabel contentTitle = new JLabel("���� ��ǥ ����");
		contentTitle.setLocation(120, 135);
		contentTitle.setSize(170, 25);
		contentTitle.setFont(contentFont);
		contentTitle.setForeground(Color.BLACK);
		c.add(contentTitle);

		// # 3-2. ���� ��
		barPanel contentBar = new barPanel();
		contentBar.setLayout(null);
		contentBar.setSize(300, 30);
		contentBar.setLocation(0, 150);
		c.add(contentBar);

		// # 4. �޴� ��ư
		// # 4-1. �н��� ���� ��ư
		PolygonButtonLeft leftMenu = new PolygonButtonLeft("�н���\n ����"); // ��ư ����
		leftMenu.setBackground(new Color(112, 173, 71));
		leftMenu.setForeground(Color.WHITE);
		leftMenu.setFont(menuFont);
		leftMenu.setLocation(0, 200); // ��ư�� ��ġ ����
		leftMenu.setSize(220, 200); //
		c.add(leftMenu);

		// # 4-2. ��ǥ ������ Ȯ�� ��ư
		PolygonButtonRight rightMenu = new PolygonButtonRight("��ǥ\n������\nȮ��"); // ��ư ����
		rightMenu.setBackground(new Color(47, 85, 151));
		rightMenu.setForeground(Color.WHITE);
		rightMenu.setFont(menuFont);
		rightMenu.setLocation(180, 200); // ��ư�� ��ġ ����
		rightMenu.setSize(225, 200); //
		c.add(rightMenu);

		// # 6. �̺�Ʈ �߰��ϱ�
		// #6-1. Home ��ư �̺�Ʈ �߰�
		homeButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// 1. ������������ �̵��ϱ�
				new MainDisplay();
				setVisible(false); // �ش� â �Ⱥ��̱�
			}
		});

		// #6-2. ���� �޴� ��ư �̺�Ʈ �߰�
		leftMenu.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				SetStudyPlan set = new SetStudyPlan();
				set.SetStudyPlan();
				setVisible(false);
			}
		});

		// #6-3. ������ �޴� ��ư �̺�Ʈ �߰�
		rightMenu.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				CheckStudyPlan check = new CheckStudyPlan();
				check.CheckStudyPlan();
				setVisible(false);
			}
		});

		setTitle("���� ��!! VOCA");
		setSize(420, 550); // ������ ũ��
		setResizable(false); // â�� ũ�⸦ �������� ���ϵ��� ����
		setVisible(true); // ������ ȭ�� ���
	}

	// �޴��� Ŭ����
	public class barPanel extends JPanel {
		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			g.setColor(Color.GRAY);
			g.fillRect(110, 20, 310, 3);
		}
	}

	// �����޴� ��ư Ŭ����
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
			// #1. ��ư ���� ����
			Graphics2D graphics = (Graphics2D) g;
			graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
			if (getModel().isArmed()) { // ���콺�� ������ ����
				graphics.setColor(getBackground().darker());
			} else if (getModel().isRollover()) { // ���콺�� �÷��� ����
				graphics.setColor(getBackground().darker());
			} else { // ����
				graphics.setColor(getBackground());
			}

			int[] x = { 0, 0, 170, 205 };
			int[] y = { 0, 200, 200, 0 };
			graphics.fillPolygon(x, y, 4);

			// #2. ��ư �̸� �߰�
			graphics.setColor(getForeground());
			graphics.setFont(getFont());
			String text = getText();
			int j = 20; // ��ư ���� x��ǥ
			int k = 25; // ��ư ���� y��ǥ
			drawString(g, text, j, k);
			graphics.dispose();
			super.paintComponent(g);

		}
	}

	// �����޴� ��ư Ŭ����
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
			// #1. ��ư ���� ����
			Graphics2D graphics = (Graphics2D) g;
			graphics.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
			if (getModel().isArmed()) { // ���콺�� ������ ����
				graphics.setColor(getBackground().darker());
			} else if (getModel().isRollover()) { // ���콺�� �÷��� ����
				graphics.setColor(getBackground().darker());
			} else { // ����
				graphics.setColor(getBackground());
			}

			int[] x = { 35, 0, 225, 225 };
			int[] y = { 0, 200, 200, 0 };
			graphics.fillPolygon(x, y, 4);

			// #2. ��ư �̸� �߰�
			graphics.setColor(getForeground());
			graphics.setFont(getFont());
			String text = getText();
			int j = 40; // ��ư ���� x��ǥ
			int k = -5; // ��ư ���� y��ǥ
			drawString(g, text, j, k);
			graphics.dispose();
			super.paintComponent(g);

		}
	}

	public static void main(String[] args) {
		new LearningManagement();
	}
}
