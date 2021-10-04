/**
 * API para remover um item do carrinho
 * request.query possui os parâmetros enviados via GET e deve conter um JSON params em formato de string, seguindo o padrão:
 * params = {
 *  user_id: 'id do usuario logado/sessao autenticada
 *  item_code: 'código do item
 * }
 * @param {} request - parâmetro padrão para tratar o request enviado a api
 * @param {} response - parâmetro padrão para tratar a resposta da api
 */
 const RemoveItemAPI = async function (request, response) {
    const res = await fetch("http://localhost:80/endpoints/remove_item_cart.php?params="+request.query.params);
    const json = await res.json();

    if (json.errors) {
        response.json({});
        throw new Error('Failed to fetch Remove Item from Cart API');
    }

    response.json(json);
}

export default RemoveItemAPI;
