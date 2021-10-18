package javagiac;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.StringSelection;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.AdjustmentEvent;
import java.awt.event.AdjustmentListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.ListCellRenderer;
import javax.swing.WindowConstants;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

/********************************************
 * Java swing single interface for giac
 * 
 * @author Diego Cueva  http://diego-cueva.com
 *  
 * Use java 1.6 or upper 
 * 
 * Code released under GLP 3 http://www.gnu.org/copyleft/gpl.html
 * 
 */
class StackElement{
	public String input;
	public String visual;
	public gen    result;
	
	public StackElement(){
		input = " ";
		visual= " ";
	}
	
	public void set(StackElement src){
		input = src.input;
		visual= src.visual;
		result=src.result;
	}
}

class Stack{

	/** STACK */
	private int stackSize;
	
    /** Giac context */
    private context C;
    
    /** Stack Elements */
    private StackElement[] elements;
    
    public Stack(int stackSize, context C){
    	this.stackSize = stackSize;
    	this.C         = C;
    	elements       = new StackElement[stackSize];
    	for(int i=0; i<stackSize; i++){
    		elements[i] = new StackElement();
    	}
    }
    
    public void put(String input, gen result){
		for(int i=0; i<stackSize-1; i++){
			elements[i].set(elements[i+1]);
		}
		
		String strResult = resultToString(result, C);
		elements[stackSize-1].visual = strResult;
		elements[stackSize-1].input  = input;
		elements[stackSize-1].result = result;
    }
    
	public int getStackSize() {
		return stackSize;
	}
	
	public void clear(){
    	for(StackElement element: elements){
    		element.input  = " ";
    		element.visual = " ";
    	}	
	} 	
	
	public String getInput(int index) {
		return elements[index].input;
	}
	public String getVisual(int index){
		return elements[index].visual;
	}
	public gen getResult(int index){
		return elements[index].result;
	}
	
	public String resultToString(gen result, context C){
		return result.print(C);
	}
}
	

public class Visual extends JFrame 
	implements KeyListener, AdjustmentListener, 
			   Runnable, WindowListener, ActionListener,
			   ListSelectionListener, ListCellRenderer{

	/** STACK SIZE !!! */
	public static final int STACK_SIZE = 150;
	
	/** Font for list elements */
	public static final Font fontList = new Font("Courier New", Font.PLAIN | Font.TRUETYPE_FONT, 14);
	
	/** Font for button elements */
	public static final Font fontButton = new Font("Arial", Font.BOLD, 11); 
	public static final Font fontButtonSmall = new Font("Arial", Font.PLAIN, 9);
	
	/** serialVersionUID */
	private static final long serialVersionUID = 1L;
	
	/** Stack de expresiones */
    private JList expressions;
    
	/** Numerador de expresiones */
    private JList numExpression;
    
    /** Para poder hacer scroll vertical */
    private JScrollPane jsrcoll;
    
    /** Caja de texto inferior comando */
    private JTextField cmdText;
    
    /** Panel for numebr list and visual expressions */
    private JPanel twoList;
    
    /** Singleton */
    private static Visual visual;
    
    /** Giac context */
    private static context C;
    
    /** Input string to be evaluated by giac */
	private String toProcess = null;
    
    /** Messages */
    private JLabel alert = new JLabel("Java GIAC interface");
    
    /** Stack */
    private Stack stack;
    
    /** Number lines */
    private String[] numberLines = new String[STACK_SIZE*2];
    
    /** Visual JLabel elements */
    private JLabel[] eLabels = new JLabel[STACK_SIZE*2];
    
    /** Variables for symbolic solve */
    private static final char vars[] = {'x', 'y', 'z', 't', 'n'};
    
    private static int indVar=0;
    
    /** Util Buttons */
    private JButton button_C = new JButton  ("C");
    private JButton button_CL = new JButton ("CL");
    private JButton button_N = new JButton  ("S=D");
    private JButton button_X = new JButton  (String.valueOf(vars[indVar]));
    private JButton button_CPY = new JButton("copy");
    private JButton button_EVA = new JButton("eval");
    
    /** Function buttons */
    private JButton[] FbButton;
    /** Labels */
    private String[] FbLabel = {
    		"root", "lcm",  "gcd",  "rand", "fact", "sipl", 
    		"fmax", "fmin", "perm", "+inf", "-inf", "limt",
    		"canf", "solv", "diff", "intg", "sum" ,  "lin"
    		};
    /** Input String */
    private String[] FbInput = {
    		"root(3,?)",         "lcm(,)",    "gcd(,)",             "rand()",   "factor(?)",   "simplify(?)", 
    		"fmax(?,?)",         "fmin(?,?)", "perm(,)",            "+infinity","-infinity",   "limit(?, ?=0)",
    		"canonical_form(?)", "solve(?=0, ?)","function_diff(?)(?)","integrate(?,?)",  "sum(?, ?, 1, +infinity)",  "lin(?)"
    		};
    static {
        try {
			// System.load("/usr/local/lib/libgiacjava.so");
        	
        	loadWindowsLibrary();
        } catch (UnsatisfiedLinkError e) {
          System.err.println("Native code library failed to load. See the chapter on Dynamic Linking Problems in the SWIG Java documentation for help.\n" + e);
          System.exit(1);
        }
      }
    
    /** 
     * Windows mechanism to load library: javagiac
     * For windows you must run in this way:
     *      java -Djava.library.path=C:\tmp\javagiac javagiac.Visual
     *  where C:\tmp\javagiac is the directory containing JNI unpacked
     */
    public static void loadWindowsLibrary(){
    	System.out.println("Loading giac java interface from: \n\t"+System.getProperty("java.library.path"));
        System.loadLibrary("javagiac");
    }
    
    /**
     * Entry point 
     * @param args
     */
	public static void main(String[] args) {
		visual = new Visual();
		Thread thread = new Thread(visual);
		thread.start();
	}
	
	/**
	 * Constructor for main frame.
	 * Create visual components and build the swing interface
	 */
	public Visual(){
		super("Java GIAC");
		
		// Init giac context
		C=new context();
		// Init stack
		stack = new Stack(STACK_SIZE, C);
		
		this.addWindowListener(this);
		this.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		
		/** Labels for stack */
		for(int i=0; i<STACK_SIZE; i++){
			eLabels[ i*2 ] = newJLabelInput();
			eLabels[i*2+1] = newJLabelResult();
			numberLines[ i*2 ] = ""+String.format("%3d", STACK_SIZE-i)+":";
			numberLines[i*2+1] = " ";
		}
		
        cmdText = new JTextField();
        cmdText.setFont( new Font("Courier New", Font.PLAIN | Font.TRUETYPE_FONT, 14) );
        
        alert.setFont( new Font("Courier New", Font.BOLD | Font.TRUETYPE_FONT, 16)  );
        alert.setForeground( Color.red );
        alert.setBackground( Color.white );
        
        expressions = new JList( eLabels  );
        expressions.setFont    ( new Font("Courier New", Font.PLAIN | Font.TRUETYPE_FONT, 14) );
        expressions.setAutoscrolls(true);
        expressions.addListSelectionListener(this);
        expressions.setCellRenderer(this);
        
        numExpression = new JList(numberLines);
        numExpression.setFont    ( new Font("Courier New", Font.BOLD | Font.TRUETYPE_FONT, 13) );
        numExpression.setAutoscrolls(true);
        numExpression.setEnabled(false);
        
        twoList = new JPanel();
        twoList.setLayout( new BorderLayout() );
        twoList.add(BorderLayout.LINE_START, numExpression);
        twoList.add(BorderLayout.CENTER, expressions);
        
        jsrcoll = new JScrollPane( JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED );
        jsrcoll.getViewport().add(twoList);

        button_C.setFont( fontButton );
        button_CL.setFont( fontButton );
        button_N.setFont( fontButton );
        button_X.setFont( new Font("Arial", Font.ITALIC | Font.BOLD, 14) );
        button_CPY.setFont( fontButtonSmall );
        button_EVA.setFont( fontButtonSmall );
        
        button_CL.setForeground(Color.red);
        button_X.setForeground(Color.blue);
        
        button_C.addActionListener(this);
        button_CL.addActionListener(this);
        button_N.addActionListener(this);
        button_X.addActionListener(this);
        button_CPY.addActionListener(this);
        button_EVA.addActionListener(this);
        
        JPanel buttonsPannel = new JPanel();
        buttonsPannel.setLayout( new GridLayout(4, 6, 10, 10) );
        buttonsPannel.add(button_N);
        buttonsPannel.add(button_EVA);
        buttonsPannel.add(button_X);
        buttonsPannel.add(button_CPY);
        buttonsPannel.add(button_CL);
        buttonsPannel.add(button_C);
        
        FbButton = new JButton[FbLabel.length];
        for(int i=0; i<FbLabel.length; i++){
        	FbButton[i] = new JButton( FbLabel[i] );
        	FbButton[i].setFont(fontButtonSmall);
        	FbButton[i].addActionListener(this);
        	buttonsPannel.add(FbButton[i]);
        }
        
        JPanel panelSouth = new JPanel();
        panelSouth.setLayout( new BorderLayout() );
        panelSouth.add( cmdText, BorderLayout.PAGE_START );
        panelSouth.add( buttonsPannel, BorderLayout.CENTER );        
        
        // Ventana principal
        setSize(400, 500);
        setLayout(new BorderLayout());   
        add(BorderLayout.NORTH, alert);
        add(BorderLayout.CENTER, jsrcoll);
        add(BorderLayout.SOUTH, panelSouth);
        
        jsrcoll.getVerticalScrollBar().addAdjustmentListener(this);
        jsrcoll.setFocusable(false);
        
        // Listeners
        cmdText.setFocusTraversalKeysEnabled(false);
        cmdText.addKeyListener(this);
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation(dim.width/2-this.getSize().width/2, dim.height/2-this.getSize().height/2);
		this.setVisible(true);
		cmdText.requestFocus();
	}

	
	/** 
	 * Thread for process
	 */
	public void run(){
		cmdText.requestFocus();
		for(;;){
			while(toProcess==null){
				synchronized (visual) {
					try {
						wait();
					} catch (InterruptedException e) {}
				}
			}
			
			try{
				/**
				 * GIAC evaluation
				 */
				String input = toProcess;
				gen g=new gen(input, C);
				gen h=giac._factor(g,C);
				h = giac._eval(h, C);
				stack.put(input, h);
				
				repaintElements();
			}catch(Throwable ee){
				alert.setText( ee.getMessage() );
				this.repaint();
				setPositionList();
				ee.printStackTrace();
			}
			toProcess = null;
			enableInputs();
			cmdText.requestFocus();
		}
	}
	
	public void setPositionList(){
		initScroll = false;
		jsrcoll.getViewport().setViewPosition(new Point(0,0));		
	}
	
	public void repaintElements(){
		twoList.repaint();
		setPositionList();
		cmdText.setText("");
		expressions.clearSelection();
		cmdText.requestFocus();
	}
	
	public JLabel newJLabelInput(){
		JLabel res = new JLabel("", JLabel.LEFT);
		res.setFont(fontList);
		return res;
	}
	public JLabel newJLabelResult(){
		JLabel res = new JLabel("", JLabel.RIGHT);
		res.setFont(fontList);
		return res;
	}	
	
	public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
		int ind = index/2;
		if( (index%2)==0 ){
			eLabels[ index ].setText( stack.getInput(ind));
		}else{
			eLabels[index].setText( stack.getVisual(ind) );
		}
		
		return eLabels[index];
	} 
	
	public void disableInputs(){
		expressions.setEnabled(false);
		cmdText.setEnabled(false);
		button_C.setEnabled(false);
		button_CL.setEnabled(false);
		button_N.setEnabled(false);
		button_CPY.setEnabled(false);
		button_EVA.setEnabled(false);		
	}
	public void enableInputs(){
		expressions.setEnabled(true);
		cmdText.setEnabled(true);
		button_X.setEnabled(true);
		button_C.setEnabled(true);
		button_CL.setEnabled(true);
		button_N.setEnabled(true);
		button_CPY.setEnabled(true);
		button_EVA.setEnabled(true);
	}	
	
	public void sendInputToProcess(String input){
		synchronized (visual) {
			toProcess = input;
			disableInputs();
			notifyAll();
		}		
	}
	
	int indCursor=(STACK_SIZE)*2+1;
	public void keyTyped(KeyEvent e) {}
	public void keyPressed(KeyEvent e) {}
	public void keyReleased(KeyEvent e) {
		alert.setText( " " );
		if(e.getKeyCode()==10){
			indCursor=(STACK_SIZE)*2+1;
			if(toProcess != null) return;
			String input = cmdText.getText().trim();
			if(input.length() <= 0) return;
			sendInputToProcess(input);
		}
		
		switch(e.getKeyCode()){
		case KeyEvent.VK_DOWN:
			if(indCursor<((STACK_SIZE)*2)+1){
				String newInput = getTextIndCursor(indCursor+1);
				if( newInput.length() > 0 ){
					cmdText.setText(newInput);
					indCursor++;	
				}
			}
			break;
		case KeyEvent.VK_UP:
			if(indCursor>1){
				String newInput = getTextIndCursor(indCursor-1);
				if( newInput.length() > 0 ){
					cmdText.setText(newInput);
					indCursor--;
				}
			}
			break;			
		}
		
	}
	
	private String getTextIndCursor(int indC){
		int ind = (indC-1)/2;
		if( ind <= STACK_SIZE-1){
			if( (indC%2)!=0 ){
				return stack.getInput(ind).trim();					
			}else{
				return stack.getVisual(ind).trim();
			}				
		}else{
			return "";
		}		
	}

	private static boolean initScroll = false;
	public void adjustmentValueChanged(AdjustmentEvent e) {
		if(!initScroll){
			initScroll = true;
			e.getAdjustable().setValue(e.getAdjustable().getMaximum());
		}
	}

	public void windowOpened(WindowEvent e) {}
	public void windowClosing(WindowEvent e) {
		System.out.println("Goodbye");
		System.exit(0);
	}
	public void windowClosed(WindowEvent e) {}
	public void windowIconified(WindowEvent e) {}
	public void windowDeiconified(WindowEvent e) {}
	public void windowActivated(WindowEvent e) {}
	public void windowDeactivated(WindowEvent e) {}

	public void valueChanged(ListSelectionEvent e) {
		if(e.getSource() == expressions && e.getValueIsAdjusting()){
			int index = expressions.getSelectedIndex();
			int ind = index/2;
			if(index >= 0){
				if( (index%2)==0 ){
					String addInput = stack.getInput(index/2);
					String previo   = cmdText.getText();
					cmdText.setText(previo+addInput);					
				}else{
					String addResult = stack.getVisual(ind);
					String previo    = cmdText.getText();
					cmdText.setText(previo+addResult);
				}
				cmdText.requestFocus();
				expressions.clearSelection();
			}
		}
	}

	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == button_C){
			cmdText.setText("");
		}
		if(e.getSource() == button_CL){
			stack.clear();
			repaintElements();
		}
		if(e.getSource() == button_N){
			gen g = stack.getResult(STACK_SIZE-1);
			if(g!=null){
				String input = "evalf("+g.print(C)+")";
				sendInputToProcess(input);
			}
		}
		if(e.getSource() == button_EVA){
			gen g = stack.getResult(STACK_SIZE-1);
			if(g!=null){
				String input = "evala("+g.print(C)+")";
				sendInputToProcess(input);
			}
		}		
		if(e.getSource() == button_X){
			indVar = (indVar+1)%vars.length;
			button_X.setText( String.valueOf(vars[indVar]) );
			button_X.repaint();
		}
		if(e.getSource() == button_CPY){
			StringBuilder text=new StringBuilder();
			
			for(int i=0; i<STACK_SIZE; i++){
				String input = stack.getInput(i).trim();
				if(input.length() > 0){
					String result = stack.getVisual(i);
					text.append(input);
					text.append("\n\t");
					text.append(result);
					text.append("\n");
				}
			}
			
			StringSelection stringSelection = new StringSelection (text.toString());
		    Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
		    clipboard.setContents(stringSelection, null);
		}
		
		/** Function buttons */
		for(int i=0; i<FbLabel.length; i++){
			if( e.getSource() == FbButton[i] ){
				cmdText.setText( FbInput[i].replace('?', vars[indVar]) );
			}
		}
		
		cmdText.requestFocus();
	}

}
