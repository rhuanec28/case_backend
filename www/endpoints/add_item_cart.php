<?php
require_once "../classes/class.addItem.inc";
// transforma o JSON enviado no params para um array
$params = json_decode($_REQUEST["params"], true);
$addItem = new addItem($params);
echo json_encode($addItem->executeAPI());