import javax.swing.*;
import java.awt.*;

public class RenderEngine {
    public static void main(String[] args) {
        JFrame frame = new MyFrame();
    }
}

class MyFrame extends JFrame {
    MyFrame() {
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Experimental environment");
        this.setResizable(false);
        this.setSize(400,737);
        this.setLayout(null);
        this.setVisible(true);
        JSlider sliderx = new JSlider(-180,180,0);
        JSlider slidery = new JSlider(-180,180,0);
        JSlider sliderz = new JSlider(-180,180,0);
        sliderx.setPreferredSize(new Dimension(400,50));
        slidery.setPreferredSize(new Dimension(400,50));
        sliderz.setPreferredSize(new Dimension(400,50));
        JLabel labelx = new JLabel("Change camera x rotation:");
        JLabel labely = new JLabel("Change camera y rotation:");
        JLabel labelz = new JLabel("Change camera z rotation:");
        labelx.setHorizontalAlignment(JLabel.CENTER);
        labely.setHorizontalAlignment(JLabel.CENTER);
        labelz.setHorizontalAlignment(JLabel.CENTER);
        labelx.setBounds(0,0,400,50);
        sliderx.setBounds(0,50,400,50);
        labely.setBounds(0,100,400,50);
        slidery.setBounds(0,150,400,50);
        labelz.setBounds(0,200,400,50);
        sliderz.setBounds(0,250,400,50);
        sliderx.setPaintTicks(true);
        sliderx.setMinorTickSpacing(30);
        sliderx.setPaintTrack(true);
        sliderx.setMajorTickSpacing(90);
        slidery.setPaintTicks(true);
        slidery.setMinorTickSpacing(30);
        slidery.setPaintTrack(true);
        slidery.setMajorTickSpacing(90);
        sliderz.setPaintTicks(true);
        sliderz.setMinorTickSpacing(30);
        sliderz.setPaintTrack(true);
        sliderz.setMajorTickSpacing(90);
        this.add(labelx);
        this.add(labely);
        this.add(labelz);
        this.add(sliderx);
        this.add(slidery);
        this.add(sliderz);
        Viewport viewport = new Viewport();
        this.add(viewport);
        sliderx.addChangeListener(e -> {
            viewport.rx = sliderx.getValue();
            viewport.repaint();
        });
        slidery.addChangeListener(e -> {
            viewport.ry = slidery.getValue();
            viewport.repaint();
        });
        sliderz.addChangeListener(e -> {
            viewport.rz = sliderz.getValue();
            viewport.repaint();
        });
    }
}

class Viewport extends JPanel {
    double fov = 90.0;
    public double rx = -35.0;
    public double ry = 0.0;
    public double rz = -45.0;
    Viewport() {
        this.setBounds(0,300,400,400);
    }
    public void paint(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;
        g2d.setPaint(Color.BLACK);
        g2d.fillRect(0,0,400,400);
        double camera_rotation[] = {Math.toRadians(this.rx),Math.toRadians(this.ry),Math.toRadians(this.rz)};
        double camera_position[] = {2,2,4};
        
        double center3d[] = {0.0,0.0,0.0};
        double x3d[] = {1.0,0.0,0.0};
        double y3d[] = {0.0,1.0,0.0};
        double z3d[] = {0.0,0.0,1.0};
        double center2d[] = transformPosition(camera_rotation,camera_position,center3d);
        double x2d[] = transformPosition(camera_rotation,camera_position,x3d);
        double y2d[] = transformPosition(camera_rotation,camera_position,y3d);
        double z2d[] = transformPosition(camera_rotation,camera_position,z3d);

        g2d.setPaint(Color.RED);
        g2d.drawLine((int)center2d[0],(int)center2d[1],(int)x2d[0],(int)x2d[1]);
        g2d.drawString("x",(int)x2d[0],(int)x2d[1]);
        g2d.setPaint(Color.GREEN);
        g2d.drawLine((int)center2d[0],(int)center2d[1],(int)y2d[0],(int)y2d[1]);
        g2d.drawString("y",(int)y2d[0],(int)y2d[1]);
        g2d.setPaint(Color.BLUE);
        g2d.drawLine((int)center2d[0],(int)center2d[1],(int)z2d[0],(int)z2d[1]);
        g2d.drawString("z",(int)z2d[0],(int)z2d[1]);
    }
    // returns 2d projection from camera rotation, camera position, point position
    public double[] transformPosition(double cr[],double cp[],double pp[]) {
        double ascx = pp[0]-cp[0]; // subtract camera position from point position
        double ascy = pp[1]-cp[1]; // subtract camera position from point position
        double ascz = pp[2]-cp[2]; // subtract camera position from point position
        // rotate around z axis
        double dx0 = Math.cos(cr[2])*ascx+Math.sin(cr[2])*ascy;
        double dy0 = Math.cos(cr[2])*ascy-Math.sin(cr[2])*ascx;
        double dz0 = ascz;
        // rotate around y axis
        double dx1 = Math.cos(cr[1])*dx0-Math.sin(cr[1])*dz0;
        double dy1 = dy0;
        double dz1 = Math.sin(cr[1])*dx0+Math.cos(cr[1])*dz0;
        // rotate around x axis
        double dx2 = dx1;
        double dy2 = Math.cos(cr[0])*dy1+Math.sin(cr[0])*dz1;
        double dz2 = Math.cos(cr[0])*dz1-Math.sin(cr[0])*dy1;
        // project onto the 2d plane
        double ez = 400/Math.tan(Math.toRadians(fov/2.0));
        double bx = 200;
        double by = 200;
        if (dz2!=0) {
            bx -= ez/dz2*dx2;
            by -= ez/dz2*dy2;
        }
        // return point
        double point[] = {bx,by};
        System.out.println(dx0+"\t"+dy0+"\t"+dz0+"\t"+dx1+"\t"+dy1+"\t"+dz1+"\t"+dx2+"\t"+dy2+"\t"+dz2+"\t"+ez);
        return point;
    }
}