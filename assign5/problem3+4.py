def square(x):
   return x*x;

def even(x):
   return (x % 2) == 0

def my_map(func, original_list):
#   return (func(x) for x in original_list)
   for x in original_list:
      yield func(x)

def my_filter(func, original_list):
#   return (x for x in original_list if func(x))
   for x in original_list:
      if func(x):
         yield x

for element in my_filter(even, my_map(square, range(5))):
   print(element)
