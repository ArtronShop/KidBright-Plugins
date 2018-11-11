Blockly.JavaScript['switch_onpressed'] = function(block) {
	var dropdown_button = block.getFieldValue('button');
	var statements_handler = Blockly.JavaScript.statementToCode(block, 'handler');
	// TODO: Assemble JavaScript into code variable.
	var code = 'DEV_IO.theIO().btn_set_callback(' + dropdown_button + ', []() { ' + statements_handler + ' });\n';
	return code;
};