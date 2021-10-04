/**
 * API para adicionar um cupom a um carrinho
 * request.query possui os parâmetros enviados via GET e deve conter um JSON params em formato de string, seguindo o padrão:
 * params = {
 *  user_id: 'id do usuario logado/sessao autenticada (teoricamente pode ser qualquer ID, já que não existe uma validação de sessão. Ao ser informado um id de usuário que ainda não possui um carrinho com itens, um novo carrinho é criado para o usuário)
 *  coupon_code: 'código do cupom'
 * }
 * @param {} request - parâmetro padrão para tratar o request enviado a api
 * @param {} response - parâmetro padrão para tratar a resposta da api
 */
 const AddCouponAPI = async function (request, response) {
    const res = await fetch("http://localhost:80/endpoints/add_coupon_cart.php?params="+request.query.params);
    const json = await res.json();

    if (json.errors) {
        response.json({});
        throw new Error('Failed to fetch Add Coupon to Cart API');
    }

    response.json(json);
}

export default AddCouponAPI;
