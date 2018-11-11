Blockly.Blocks['switch_onpressed'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.BUTTON_EVENT_ON_PRESSED_TITLE1)
			.appendField(new Blockly.FieldDropdown([["S1","1"], ["S2","2"]]), "button")
			.appendField(Blockly.Msg.BUTTON_EVENT_ON_PRESSED_TITLE2);
		this.appendStatementInput("handler")
			.setCheck(null);
		this.setColour(165);
		this.setTooltip(Blockly.Msg.BUTTON_EVENT_ON_PRESSED_TOOLTIP);
		this.setHelpUrl("");
	}
};