;fibonacci series ka hisaab karnay and dekhanay wala program
kaam markazi@khali () karo
    rakho n@adad := 5;
    rakho y := n/6*7;
    agar (n < 0) to phir karo  
		dekhao << `munfi number daal diya\n`;
		wapas bhaijo 0; 
	warna agar (n < 0) to phir
		dekhao << `yar 0 hai!\n`;
		wapas bhaijo 0;
	warna phir
		dekhao << `\nfibonacci series: `; 
		rakho i@adad := 1;
		jab tak (i-1 >= n) karo
			dekhao << x << ` `;	
			rakho z := x+y ;		
			rakho x := y;
			rakho y := z;
			rakho i := i + 1;
		bas karo
	bas karo


kaam khatam