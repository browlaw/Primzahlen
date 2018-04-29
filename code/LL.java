package lucas_Lehmer;

public class LL {

	public static void main(String[] args) {
		
		int p = 31;
		boolean prime = Lucas(p);
		System.out.print(" ist ");
		if (!prime) {
			System.out.print("keine ");
		}
		System.out.print("Mersenne Prime");

	}

	private static boolean Lucas(int p) {
		long wert = 4;
		long prim = (long)Math.pow(2, p)-1;
		System.out.print(prim);
		for (int i = 0; i < p-2; i++) {
			wert = (wert*wert-2) % prim;			
		}
		if (wert == 0) {
			return true;			
		}else {
		return false;
		}
	}

}
