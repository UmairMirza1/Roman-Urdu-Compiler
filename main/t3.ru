;fibonacci series ka hisaab karnay and dekhanay wala program
kaam markazi@khali () karo
	rakho num@adad;
	lo << `Enter the number` >> num; input
	dekhao << num << ` `;

	rakho num := num + 5;
	dekhao << num << `\n`;

	rakho num := num - 5;
	dekhao << num << `\n`;

	rakho num := num * 2;
	dekhao << num << `\n`;

	rakho num := num / 2;
	dekhao << num << `\n`;

	rakho num := num % 2;
	dekhao << num << `\n`;

	rakho i@adad := 0;
	jab tak (i = 10) karo
			dekhao << i << ` `;
			rakho i := i + 1;
	bas karo
	dekhao << `\n`;

	rakho n@adad := 1;
	agar (n = 1) to phir karo
		dekhao << `aik daal diya\n`;
	warna agar (n = 0) to phir
		dekhao << `yar 0 hai!\n`;
	warna phir
		dekhao << `\nhan ab sahi hay: `;
	bas karo
kaam khatam