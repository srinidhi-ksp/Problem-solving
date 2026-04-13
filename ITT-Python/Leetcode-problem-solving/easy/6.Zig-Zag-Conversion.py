class Solution:
    def convert(self, s: str, numRows: int) -> str:
        if numRows == 1 or numRows >= len(s):
            return s
        res=[]
        cycle_len = 2 * (numRows - 1)
        
        for i in range(numRows):
            row= []
            for j in range(i, len(s), cycle_len):
                row.append(s[j])    #all main vertical elements will be added
                diag=j+cycle_len-2*i  #next diagonal index possible
                if i!=0 and i!=numRows-1 and diag<len(s):   #add element in diagonal index 
                    row.append(s[diag])
            res.append("".join(row))
        return "".join(res)
                 
