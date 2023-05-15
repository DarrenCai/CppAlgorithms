/**
 * 几何平均值最大子数组
 * 2023 Q1
 */

import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();int l = sc.nextInt();
        double[] numbers = new double[n];
        for (int i = 0; i < n; i++) {
            numbers[i] = sc.nextDouble();
        }
        System.out.println(getResult(n, l, numbers));
    }
    public static String getResult(int n, int l, double[] numbers) {
        double minAvg = Integer.MAX_VALUE;
        double maxAvg = Integer.MIN_VALUE;
        for (double num : numbers) {
            minAvg = Math.min(num, minAvg);m
            axAvg = Math.max(num, maxAvg);
        }
        double diff = maxAvg / Math.pow(10, 10);
        int[] ans = new int[2];
        while (maxAvg - minAvg >= diff) {
            double midAvg = (minAvg + maxAvg) / 2;
            if (check(n, l, numbers, midAvg, ans)) {
                minAvg = midAvg;
            } else {
                maxAvg = midAvg;
            }
        }
        return ans[0] + " " + ans[1];
    }
    public static boolean check(int n, int l, double[] numbers, double avg, int[] ans) {
        double fact = 1;
        for (int i = 0; i < l; i++) {
            fact *= numbers[i] / avg;
        }
        if (fact >= 1) {
            ans[0] = 0;
            ans[1] = l;
            return true;
        }
        double pre_fact = 1;
        double min_pre_fact = Integer.MAX_VALUE;
        int min_pre_fact_end = 0;
        for (int i = l; i < n; i++) {
            fact *= numbers[i] / avg;
            pre_fact *= numbers[i - l] / avg;
            if (pre_fact < min_pre_fact) {
                min_pre_fact = pre_fact;
                min_pre_fact_end = i - l;
            }
            if (fact / min_pre_fact >= 1) {
                ans[0] = min_pre_fact_end + 1;
                ans[1] = i - min_pre_fact_end;
                return true;
            }
        }
        return false;
    }
}