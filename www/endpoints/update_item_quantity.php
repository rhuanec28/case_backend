<?php
require_once "../classes/class.updateItem.inc";
// transforma o JSON enviado no params para um array
$params = json_decode($_REQUEST["params"], true);
$updateItem = new updateItem($params);
echo json_encode($updateItem->executeAPI());