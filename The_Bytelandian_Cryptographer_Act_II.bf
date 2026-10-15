,>,>,           Read the 3-digit number into cell 0, 1, and 2
+               Increment the third digit (cell 2)

[>+>+<<-]       Copy cell 2 to cell 3 and 4
>[<+>-]         Restore cell 2 from cell 3
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Put exactly 58 in cell 3 (ASCII for ':')
>[<->-]<        Subtract cell 4 from cell 3 (cell 3 = 58 - digit). Result is ALWAYS >= 0!
>+<             Set cell 4 as a flag (1)
[>-<[-]]        If cell 3 is NOT 0 (meaning digit is not 58), clear the flag
>               Move to flag (cell 4)
[               If flag is still 1 (meaning the digit became 10)
  [-]           Clear the flag
  <<            Move to cell 2 (third digit)
  ----------    Subtract 10 to turn ':' (58) into '0' (48)
  <+            Move to cell 1 (second digit) and increment it (CARRY 1)
  >>>           Return to cell 4 to end loop
]

<<<             Move back to cell 1 (second digit)
[>>+>+<<<-]     Copy cell 1 to cell 3 and 4
>>[<<+>>-]      Restore cell 1 from cell 3
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Put exactly 58 in cell 3
>[<->-]<        Subtract cell 4 from cell 3 (cell 3 = 58 - digit).
>+<             Set cell 4 as a flag (1)
[>-<[-]]        If cell 3 is NOT 0 (no carry), clear the flag
>               Move to flag (cell 4)
[               If flag is still 1 (meaning the second digit became 10)
  [-]           Clear the flag
  <<<           Move to cell 1 (second digit)
  ----------    Subtract 10 to turn ':' (58) into '0' (48)
  <+            Move to cell 0 (first digit) and increment it (CARRY 1)
  >>>>          Return to cell 4 to end loop
]

<<<<            Move back to cell 0 (first digit)
.>.>.           Print the final decrypted 3-digit number!