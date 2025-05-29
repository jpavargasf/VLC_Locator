import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.ImageIcon;
import javax.swing.JLabel;


public class ImageProcessing {
	
	private BufferedImage mImage;
	
	
	public ImageProcessing() {
		mImage = null;
	}
	
	public ImageProcessing(File imageFile) {
		loadImage(imageFile);
	}
	
	
	public BufferedImage getImage() {
		return mImage;
	}
	
	public void setImage(BufferedImage image) {
		mImage = image;
	}
	
	public void loadImage(File imageFile) {
		try {
			mImage = ImageIO.read(imageFile);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void displayImage() {
		displayImage(mImage);
	}
	
	public static void displayImage(BufferedImage image) {
		if(image == null)	return;
/*		
		Graphics2D g2D = (Graphics2D) image.getGraphics();
		g2D.drawImage(image, 0, 0, 0, 0, 0, 0, 0, 0, null);
		g2D.dispose();
*/		
		ImageIcon imageIcon = new ImageIcon(image);
		JLabel jLabel = new JLabel(imageIcon);
		JFrame frame = new JFrame();
		frame.add(jLabel);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();
		frame.setVisible(true);
	}
	
	public void rgb2gray() {
		mImage = rgb2gray(mImage);
	}
	
	//no matlab é a seguinte fórmula
	//0.2989 * R + 0.5870 * G + 0.1140 * B 
	public static BufferedImage rgb2gray(BufferedImage image) {
		if(image == null)	return null;
		
		//Color color;
		int width = image.getWidth();
		int height = image.getHeight();
		
		int red, blue, green;
		double fRed, fBlue, fGreen;
		double luminance;
		int grayLevel;
		
		BufferedImage resultImage = new BufferedImage(width, height, 
				BufferedImage.TYPE_BYTE_GRAY);
		
		 for(int i = 0; i < width; i++) {
			 for(int j = 0; j < height; j++) {
				 blue = image.getRGB(i, j);
				 red = (blue >> 16) & 0xff;
				 green = (blue >> 8) & 0xff;
				 blue = blue & 0xff;
				 
				 fRed = Math.pow(red / 255.0, 2.2);
				 fGreen = Math.pow(green / 255.0, 2.2);
				 fBlue = Math.pow(blue / 255.0, 2.2);

				 luminance = 0.2126 * fRed + 0.7152 * fGreen + 0.0722 * fBlue;

				 grayLevel = (int) (255.0 * Math.pow(luminance, 1.0 / 2.2));
				 
				 //luminance = 0.2989 * red + 0.5870 * green + 0.1140 * blue; 
				 //grayLevel = (int) luminance;
				 grayLevel = (grayLevel << 16) + (grayLevel << 8) + grayLevel; 
				 resultImage.setRGB(i, j, grayLevel);
			 }
		 }		 
		 return resultImage;	
	}
	
	public void blur(int filterOrder) {
		if(filterOrder <= 0)	return;
		
		
		double[][] blurFilter = new double[filterOrder][filterOrder];
		
		double denominator = Math.pow(filterOrder, 2);
		
		for(int i = 0; i < filterOrder; i++) {
			for(int j = 0; j < filterOrder; j++) {
				blurFilter[i][j] = 1 / denominator;
			}
		}
		filter(blurFilter);
	}
	
	public void filter(double[][] filter) {
		mImage = imgFilter(mImage, filter);
	}
	
	public static BufferedImage imgFilter(BufferedImage image, double[][] filter) {
		if(image == null || filter == null)	return image;
		
		int width = image.getWidth();
		int height = image.getHeight();
		
		int filterWidth = filter.length;
		int filterHeight = filter[0].length;
		
		final int itW = filterWidth / 2;
		final int itH = filterHeight / 2;
		
		final int itWsup;
		final int itHsup;
		
		if(filterWidth % 2 == 0) {
			itWsup = itW - 1;
		}else {
			itWsup = itW;
		}
		
		if(filterHeight % 2 == 0) {
			itHsup = itH - 1;
		}else {
			itHsup = itH;
		}
		
		
		double pixelResult;
		int pixR;
		
		int itpW, itpH;
		
		BufferedImage returnImage = new BufferedImage(width, height, image.getType());
		
		int w, h, ftW, ftH;
		
		//com o while consigo melhor otimização do que com o for
		w = 0;
		while(w < width) {
			h = 0;
			while(h < height) {
				pixelResult = 0;
				
				if((w - itW) < 0) {
					ftW = - w;
				}else {
					ftW = - itW;
				}
				while(ftW <= itWsup) {
					itpW = ftW + w;
					
					if(itpW >= width)	break;
					
					if((h - itH) < 0) {
						ftH = - h;
					}else {
						ftH = - itH;
					}
					while(ftH <= itHsup) {
						itpH = ftH + h;
						
						if(itpH >= height)	break;
						
						pixelResult += (image.getRGB(itpW, itpH) & 0xff)*filter[ftW + itW][ftH + itH];
						
						
						ftH++;
					}
					
					
					
					
					ftW++;
				}
				
				pixR = (int) pixelResult;
				pixR = (pixR << 16) + (pixR << 8) + (pixR);
				returnImage.setRGB(w, h, pixR);
				
				
				h++;
			}
			
			
			w++;
		}
		/*
		for(int w = 0; w < width; w++) {
			for(int h = 0; h < height; h++) {
				pixelResult = 0;
				
				for(int ftW = -itW; ftW <= itWsup; ftW++) {
					itpW = ftW + w;
					if(itpW >= 0) {
						if(itpW < width) {
							for(int ftH = -itH; ftH <= itHsup; ftH++) {
								itpH = ftH + h;
								if(itpH >= 0) {
									if(itpH < height) {
										pixelResult += (image.getRGB(itpW, itpH) & 0xff)*filter[ftW + itW][ftH + itH];
									}
								}else {
									ftH = 
								}
								if(itpH >= 0 && itpH < height) {
									pixelResult += (image.getRGB(itpW, itpH) & 0xff)*filter[ftW + itW][ftH + itH];
								}

							}
						}	
					}
					
				}
				pixR = (int) pixelResult;
				pixR = (pixR << 16) + (pixR << 8) + (pixR);
				returnImage.setRGB(w, h, pixR);
			}
		}
		*/
		return returnImage;
		
	}
	
	//assume que a imagem já está em grayscale
	public static int[] imageHistogram(BufferedImage image) {
		if(image == null)	return null;
		
		int[] histogram = new int[256];
		
		int width = image.getWidth();
		int height = image.getHeight();
		
		//array já é inicializado com 0
		/*
		for(int i = 0; i < 256; i++) {
			histogram[i] = 0;
		}
		*/
		
		for(int i = 0; i < width; i++) {
			for(int j = 0; j< height; j++) {
				histogram[image.getRGB(i, j) & 0xff]++;
			}
		}
		
		return histogram;
	}
	
	public static int calculateOtsuLevel(BufferedImage image) {
		int otsuLevel;
		
		if(image == null)	return -1;
		
		otsuLevel = 255/2;
		
		return otsuLevel;
	}
	
	public void binarizeImage() {
		mImage = binarizeImage(mImage);
	}
	
	public static BufferedImage binarizeImage(BufferedImage image) {
		if(image == null)	return null;
		
		int width = image.getWidth();
		int height = image.getHeight();
		
		BufferedImage returnImage = new BufferedImage(width, height,
				BufferedImage.TYPE_BYTE_BINARY);
		
		//todo
		
		
		return returnImage;
	}
	
}
