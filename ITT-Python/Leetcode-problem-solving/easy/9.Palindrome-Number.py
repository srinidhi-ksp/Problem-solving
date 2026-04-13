class Solution:
    def isPalindrome(self, x: int) -> bool:
        lent = len(str(x))  
        result = 0 
        temp = x
        if(x<0):
            return False
        for i in range(lent): 
            digit = temp % 10   
            result = result * 10 + digit 
            temp = temp // 10
        return result == x  
