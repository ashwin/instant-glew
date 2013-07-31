varying vec3 normal;
varying vec3 lightDir;

void main()
{
	float intensity;
	vec3 n;
	vec4 color;
	
	n = normalize(normal);
	intensity = max(dot(lightDir, n), 0); 

	if (intensity > 0.97)
		color = vec4(1, .8, .8, 1.0);
	else if (intensity > 0.25)
		color = vec4(.8, 0, .8, 1.0);	
	else
		color = vec4(.4, 0, .4, 1.0);

	gl_FragColor = color;
}
