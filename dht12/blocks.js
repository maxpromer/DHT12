Blockly.Blocks['dht12_read_temperature'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.DHT12_READ_TEMPERATURE_MESSAGE,
			"output": "Number",
			"colour": 135,
			"tooltip": Blockly.Msg.DHT12_READ_TEMPERATURE_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['dht12_read_humidity'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.DHT12_READ_HUMIDITY_MESSAGE,
			"output": "Number",
			"colour": 135,
			"tooltip": Blockly.Msg.DHT12_READ_HUMIDITY_TOOLTIP,
			"helpUrl": ""
		});
	}
};
