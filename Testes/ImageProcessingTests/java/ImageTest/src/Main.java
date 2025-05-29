import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.ImageIcon;
import javax.swing.JLabel;

public class Main {

	//static BufferedImage mImage;
	
	
	
	public static void main(String[] args) {
		//mImage = null;
		System.out.println("Hello World!");
		/*
		try {
			mImage = ImageIO.read(new File("../../SourceFiles/01.jpg"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		//mImage.
		System.out.println(mImage.toString());
		displayImage(mImage);
		*/
		
		GSIP gsip = new GSIP(new File("../../SourceFiles/test.jpg"));
		gsip.displayImage();
		//gsip.rgb2gray();
		//gsip.displayImage();
		gsip.blur(50);
		gsip.displayImage();
		System.out.println("GSIP Done.");
		
		ImageProcessing ip = new ImageProcessing(new File("../../SourceFiles/test.jpg"));
		ip.displayImage();
		ip.rgb2gray();
		ip.displayImage();
		ip.blur(50);
		ip.displayImage();
		System.out.println("Done.");
	}
	/*
	private static void displayImage(BufferedImage image) {
		if(image == null)	return;
		ImageIcon imageIcon = new ImageIcon(image);
		JLabel jLabel = new JLabel(imageIcon);
		JFrame frame = new JFrame();
		frame.add(jLabel);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();
		frame.setVisible(true);
	}
*/
}

/*
 * 
 * Color myWhite = new Color(255, 255, 255); // Color white
int rgb = myWhite.getRGB();

try {
    BufferedImage img = null;
    try {
        img = ImageIO.read(new File("bubbles.bmp"));
    }
    catch (IOException e) {
    }

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            img.setRGB(i, j, rgb);
        }
    }

    // retrieve image
    File outputfile = new File("saved.png");
    ImageIO.write(img, "png", outputfile);
}
catch (IOException e) {
}
*/
