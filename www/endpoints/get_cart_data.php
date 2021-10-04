<?php
require_once "../classes/class.getCart.inc";

//get cart logic
$getCart = new GetCart();
echo $getCart->getCartData();
