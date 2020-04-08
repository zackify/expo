import { useEffect, useState } from 'react';
import { AuthRequest } from './AuthRequest';
import { resolveDiscoveryAsync } from './Discovery';
import { requestAsync } from './Fetch';
export function useDiscovery(issuerOrDiscovery) {
    const [discovery, setDiscovery] = useState(null);
    useEffect(() => {
        resolveDiscoveryAsync(issuerOrDiscovery).then(discovery => {
            setDiscovery(discovery);
        });
    }, [issuerOrDiscovery]);
    return discovery;
}
export function useJsonFetchRequest(accessToken, requestUrl, headers, method = 'GET') {
    const [json, setJson] = useState(null);
    const [error, setError] = useState(null);
    useEffect(() => {
        if (accessToken) {
            requestAsync(requestUrl, {
                // @ts-ignore
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                    ...headers,
                },
                method,
                dataType: 'json',
            })
                .then(json => {
                setJson(json);
                setError(null);
            })
                .catch(error => {
                setJson(null);
                setError(error);
            });
        }
    }, [accessToken]);
    return [json, error];
}
export function useAuthRequest(config, discovery) {
    const [request, setRequest] = useState(null);
    useEffect(() => {
        if (config && discovery) {
            AuthRequest.buildAsync({
                ...config,
            }, discovery).then(request => setRequest(request));
        }
    }, [
        discovery?.authorizationEndpoint,
        config.clientId,
        config.redirectUri,
        config.scopes.join(','),
        config.clientSecret,
        config.codeChallenge,
        config.state,
        JSON.stringify(config.extraParams || {}),
        config.usePKCE,
    ]);
    return request;
}
//# sourceMappingURL=AuthRequestHooks.js.map