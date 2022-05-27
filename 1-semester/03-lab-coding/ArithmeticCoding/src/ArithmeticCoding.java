import java.math.BigInteger;
import java.util.Scanner;

public class ArithmeticCoding {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.nextLine();
        String s = scanner.nextLine();

        BigInteger l = BigInteger.ZERO, r = BigInteger.ONE, z = BigInteger.ONE;
        int[] cnt = new int[n];
        for (Character c : s.toCharArray()) {
            cnt[c - 'a']++;
        }

        System.out.println(n);
        for (int i = 0; i < n; i++) {
            System.out.print(String.format("%d ", cnt[i]));
        }
        System.out.print(System.lineSeparator());

        BigInteger len = BigInteger.valueOf(s.length());
        for (Character c : s.toCharArray()) {
            z = z.multiply(len);
            BigInteger dif = r.subtract(l);
            int new_l = 0;
            for (char ch = 'a'; ch < c; ch++) {
                new_l += cnt[ch - 'a'];
            }
            int new_r = new_l + cnt[c - 'a'];
            l = l.multiply(len);
            r = l.add(dif.multiply(BigInteger.valueOf(new_r)));
            l = l.add(dif.multiply(BigInteger.valueOf(new_l)));

        }

        System.out.println(l + "/" + z + " " + r + "/" + z);

        BigInteger qq = BigInteger.valueOf(2);
        int q = 1;
        while (true) {
            BigInteger p = (l.multiply(qq).add(z).subtract(BigInteger.ONE)).divide(z);
            if (p.compareTo(qq) == -1 && p.multiply(z).compareTo(qq.multiply(r)) == -1) {
                print(p, q);
                break;
            }
            q++;
            qq = qq.multiply(BigInteger.TWO);
        }
    }

    static void print(BigInteger p, int q) {
        StringBuilder ans = new StringBuilder();
        while (p.compareTo(BigInteger.ZERO) != 0) {
            ans.append(p.and(BigInteger.ONE));
            p = p.divide(BigInteger.TWO);
        }
        while (ans.length() < q) {
            ans.append("0");
        }
        ans.reverse();
        System.out.println(ans.toString());
    }
}
