Blockly.JavaScript['dht12_read_temperature'] = function(block) {
	var code = 'DEV_I2C1.DHT12(0, 0x5C).readTemperature()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['dht12_read_humidity'] = function(block) {
	var code = 'DEV_I2C1.DHT12(0, 0x5C).readHumidity()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

