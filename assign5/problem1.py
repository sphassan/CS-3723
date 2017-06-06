def decimate_list(original_list, factor):
   decimated_list = []
   index = 0;
   for element in original_list:
      if index % factor == 0:
         decimated_list.append(element)
      index += 1
   return decimated_list

print(decimate_list(range(10), 3)) # prints [0, 3, 6, 9]
