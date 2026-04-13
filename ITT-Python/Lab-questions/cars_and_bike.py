t=int(input("Enter the no of testcase:"))
if (t<=1 or t>=100):
   print("Invalid number of testcases")
   exit(0)
for i in range(1,t+1):
   print("Testcase ",i,": ")
   n=int(input("Enter the number of tyres Ravi has :"))
   if(n<=2 or n>=1000):
       print("Invalid no. of tyres")
       continue
   if (n%4==0):
      print("NO , Ravi has manufactured only cars")
   elif (n%2==0):
          print("Yes, Ravi has manufactured bike")
   else:
          print("No, Ravi has not manufactured any bike or car")
