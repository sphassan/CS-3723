def decimate_list_gen(original_list, factor):
   index = 0
   for element in original_list:
      if index % factor == 0:
         yield element
      index += 1

for element in decimate_list_gen(range(10), 3):
   print(element)
