import java.lang.Math;

class PiApproximation
{
	private static double radius = 1;

	private static double height(double base, double hypotenuse)
	{
		return(Math.sqrt(hypotenuse*hypotenuse - base*base));
	}

	private static double circle_pi(int rectangles)
	{
		double sum, width;

		sum = 0;
		width = radius/rectangles;

		for (int i = 0; i < rectangles; i++)
		{
			sum += width*height((0.5+i)*width, radius);
		}

		return(4*sum);
	}

	private static double leibniz_pi(int iterations)
	{
		int denominator = 1;
		double sum = 0;

		while (denominator < iterations*2)
		{
			if ((denominator/2) % 2 == 0)
			{
				sum += 1.0/denominator;
			}
			else
			{
				sum -= 1.0/denominator;
			}

			denominator += 2;
		}

		return(4*sum);
	}

	public static void main(String[] args)
	{
		System.out.println("Approximations for pi");
		System.out.println("Iterations      Circle Method   Leibniz Method");
		System.out.println("----------------------------------------------");

		for (int i = 1; i <= 1000000; i *= 10)
		{
			double circle_result = circle_pi(i);
			double leibniz_result = leibniz_pi(i);
			System.out.println(String.format("%10d%20.12f%16.12f", i, circle_result, leibniz_result));
		}
	}
}

