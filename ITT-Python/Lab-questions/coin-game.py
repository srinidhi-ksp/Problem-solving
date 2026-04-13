t=int(input("Enter the no of testcase:"))
if (t<=1 or t>=1000):
   print("Invalid number of testcases")
   exit(0)
for i in range(1,t+1):
   print("Testcase ",i,": ")
   a=int(input("Enter no of coins suresh has:"))
   b=int(input("Enter no of coins sundar has:"))
   c=int(input("Enter no of coins raja has:"))
   d=int(input("Enter no of coins sarvesh has:"))

   if(a<=0 or b<=0 or c<=0 or d<=0 or a>=1000000 or b>=1000000 or c>=1000000 or d>=1000000):
       print("Invalid no. of coins")
       continue
   if a<=b:
       a+=b
   else:
       b+=c
   if a<=b:
       a=a+d
   else:
       b=b+d
   print("N   Suresh is winning") if a>=b else print("S   Sundar is winning")
