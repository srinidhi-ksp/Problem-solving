class Solution {
    public String intToRoman(int num) {
        StringBuilder result = new StringBuilder();

        // Thousands place
        if (num / 1000 != 0) {
            int m = num / 1000;
            for (int i = 0; i < m; i++) {
                result.append("M");
            }
            num = num % 1000;
        }

        // Nine hundreds (900)
        if (num >= 900) {
            result.append("CM");
            num -= 900;
        }

        // Five hundreds (500)
        if (num >= 500) {
            result.append("D");
            num -= 500;
        }

        // Four hundreds (400)
        if (num >= 400) {
            result.append("CD");
            num -= 400;
        }

        // Hundreds place (100-300)
        if (num / 100 != 0) {
            int c = num / 100;
            for (int i = 0; i < c; i++) {
                result.append("C");
            }
            num = num % 100;
        }

        // Ninety (90)
        if (num >= 90) {
            result.append("XC");
            num -= 90;
        }

        // Fifty (50)
        if (num >= 50) {
            result.append("L");
            num -= 50;
        }

        // Forty (40)
        if (num >= 40) {
            result.append("XL");
            num -= 40;
        }

        // Tens place (10-30)
        if (num / 10 != 0) {
            int x = num / 10;
            for (int i = 0; i < x; i++) {
                result.append("X");
            }
            num = num % 10;
        }

        // Nine (9)
        if (num == 9) {
            result.append("IX");
            num -= 9;
        }

        // Five (5)
        if (num >= 5) {
            result.append("V");
            num -= 5;
        }

        // Four (4)
        if (num == 4) {
            result.append("IV");
            num -= 4;
        }

        // Ones place (1-3)
        if (num > 0) {
            for (int i = 0; i < num; i++) {
                result.append("I");
            }
        }

        return result.toString();
    }
}
