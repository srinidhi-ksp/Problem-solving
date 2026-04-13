class Solution:
    def generateParenthesis(self, n: int) -> list[str]:
        stack = [("", 0, 0)]
        result = []

        while stack:
            s, open_c, closed_c = stack.pop()
            if len(s) == 2 * n:
                result.append(s)
                continue
            if closed_c < open_c:
                stack.append((s + ")", open_c, closed_c + 1))
            if open_c < n:
                stack.append((s + "(", open_c + 1, closed_c))
        
        return result
