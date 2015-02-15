package pikavision;

import pikavision.PikaVisionLibrary;
import pikavision.LineResult;

public class test
{
	public static void main(String[] args)
	{

		System.out.println("Hello World!");
		PikaVisionLibrary.InstanceStore store = PikaVisionLibrary.INSTANCE.initCamera(0);
		//PikaVisionLibrary.InstanceStore store = PikaVisionLibrary.INSTANCE.initFeed("/home/silvea/Documents/Robotics/2015/OpenCV/sampleVideo/out.flv");
		if (PikaVisionLibrary.setThreshold(store, 234) != 1) // Is optional
		{
			PikaVisionLibrary.INSTANCE.closeCamera(store);
			return;
		}

		LineResult result = PikaVisionLibrary.INSTANCE.processFrame(store);
		while (result.isProcessed == 1)
		{
			if (result.isGood == 1)
			{
				System.out.print("X pos: " + result.xPos + ", width: " + result.width + ", rotation: ");
				switch (result.rotation)
				{
					case PikaVisionLibrary.rotation_t.NONE: // int 0
						System.out.println("NONE");
						break;
					case PikaVisionLibrary.rotation_t.CLOCKWISE: // int 1
						System.out.println("CLOCKWISE");
						break;
					case PikaVisionLibrary.rotation_t.ANTICLOCKWISE: // int -1
						System.out.println("ANTI-CLOCKWISE");
						break;
				}
			}
			result = PikaVisionLibrary.INSTANCE.processFrame(store);
		}
		PikaVisionLibrary.INSTANCE.closeCamera(store);
	}
}
