class Add:
  def __init__(self, a, b):
    self.a = a; self.b = b
  def add(self):
    return self.a + self.b

#	a = 3; b = 2912   
a = int(input("Enter an integer: "))
b = int(input("Enter another integer to add: "))
Sum = Add(a, b)
print("%d + %d = %d" % (a, b, Sum.add()))
