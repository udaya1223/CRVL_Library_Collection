% Intrinsic and Extrinsic Camera Parameters
%
% This script file can be directly excecuted under Matlab to recover the camera intrinsic and extrinsic parameters.
% IMPORTANT: This file contains neither the structure of the calibration objects nor the image coordinates of the calibration points.
%            All those complementary variables are saved in the complete matlab data file Calib_Results.mat.
% For more information regarding the calibration model visit http://www.vision.caltech.edu/bouguetj/calib_doc/


%-- Focal length:
fc = [ 534.722213555334290 ; 535.183681773283640 ];

%-- Principal point:
cc = [ 318.659028861994330 ; 240.597141331007260 ];

%-- Skew coefficient:
alpha_c = 0.000000000000000;

%-- Distortion coefficients:
kc = [ 0.037515871786674 ; -0.125648751522076 ; -0.001152852850169 ; 0.001134015096891 ; 0.000000000000000 ];

%-- Focal length uncertainty:
fc_error = [ 5.164977400288923 ; 5.214839193243043 ];

%-- Principal point uncertainty:
cc_error = [ 5.239589451610659 ; 4.487333864878146 ];

%-- Skew coefficient uncertainty:
alpha_c_error = 0.000000000000000;

%-- Distortion coefficients uncertainty:
kc_error = [ 0.012336660487484 ; 0.028057902029432 ; 0.002263144960317 ; 0.002518636507230 ; 0.000000000000000 ];

%-- Image size:
nx = 640;
ny = 480;


%-- Various other variables (may be ignored if you do not use the Matlab Calibration Toolbox):
%-- Those variables are used to control which intrinsic parameters should be optimized

n_ima = 23;						% Number of calibration images
est_fc = [ 1 ; 1 ];					% Estimation indicator of the two focal variables
est_aspect_ratio = 1;				% Estimation indicator of the aspect ratio fc(2)/fc(1)
center_optim = 1;					% Estimation indicator of the principal point
est_alpha = 0;						% Estimation indicator of the skew coefficient
est_dist = [ 1 ; 1 ; 1 ; 1 ; 0 ];	% Estimation indicator of the distortion coefficients


%-- Extrinsic parameters:
%-- The rotation (omc_kk) and the translation (Tc_kk) vectors for every calibration image and their uncertainties

%-- Image #1:
omc_1 = [ 2.241603e+00 ; 2.111529e+00 ; 2.086062e-01 ];
Tc_1  = [ -3.032599e+02 ; -8.366111e+01 ; 1.069120e+03 ];
omc_error_1 = [ 2.118366e-02 ; 2.465221e-02 ; 5.318050e-02 ];
Tc_error_1  = [ 1.070562e+01 ; 9.131786e+00 ; 1.173986e+01 ];

%-- Image #2:
omc_2 = [ -2.045000e+00 ; -2.048438e+00 ; 1.888050e-01 ];
Tc_2  = [ -4.055725e+02 ; -6.336410e+01 ; 9.875392e+02 ];
omc_error_2 = [ 9.391174e-03 ; 7.435700e-03 ; 1.461624e-02 ];
Tc_error_2  = [ 9.898754e+00 ; 8.588175e+00 ; 9.899686e+00 ];

%-- Image #3:
omc_3 = [ -1.934077e+00 ; -1.821997e+00 ; -3.146797e-01 ];
Tc_3  = [ -3.683244e+01 ; -5.204527e+01 ; 8.820141e+02 ];
omc_error_3 = [ 7.404353e-03 ; 9.769424e-03 ; 1.560379e-02 ];
Tc_error_3  = [ 8.661089e+00 ; 7.368760e+00 ; 8.102918e+00 ];

%-- Image #4:
omc_4 = [ 2.012429e+00 ; 1.720110e+00 ; 3.105061e-01 ];
Tc_4  = [ -2.656108e+02 ; -2.818072e+01 ; 7.977590e+02 ];
omc_error_4 = [ 9.193930e-03 ; 8.837545e-03 ; 1.584475e-02 ];
Tc_error_4  = [ 8.025563e+00 ; 6.835186e+00 ; 8.397272e+00 ];

%-- Image #5:
omc_5 = [ -1.994937e+00 ; -2.159724e+00 ; 5.227738e-01 ];
Tc_5  = [ 1.390747e+02 ; -1.183641e+02 ; 1.162613e+03 ];
omc_error_5 = [ 1.384014e-02 ; 1.528357e-02 ; 2.708299e-02 ];
Tc_error_5  = [ 1.153247e+01 ; 9.708072e+00 ; 1.029158e+01 ];

%-- Image #6:
omc_6 = [ -2.075957e+00 ; -1.964236e+00 ; -5.774754e-01 ];
Tc_6  = [ -1.170807e+02 ; -1.562382e+02 ; 1.259957e+03 ];
omc_error_6 = [ 1.122905e-02 ; 1.228354e-02 ; 2.242548e-02 ];
Tc_error_6  = [ 1.237577e+01 ; 1.058992e+01 ; 1.288591e+01 ];

%-- Image #7:
omc_7 = [ 2.020827e+00 ; 1.989096e+00 ; 1.064287e+00 ];
Tc_7  = [ -8.411271e+01 ; 4.835219e+01 ; 4.434624e+02 ];
omc_error_7 = [ 1.061954e-02 ; 3.934311e-03 ; 1.284926e-02 ];
Tc_error_7  = [ 4.399057e+00 ; 3.763938e+00 ; 5.050014e+00 ];

%-- Image #8:
omc_8 = [ -2.648169e+00 ; -1.432013e+00 ; -4.118971e-01 ];
Tc_8  = [ -3.016352e+02 ; 6.950647e+01 ; 6.985016e+02 ];
omc_error_8 = [ 1.023125e-02 ; 5.998472e-03 ; 1.749723e-02 ];
Tc_error_8  = [ 7.012679e+00 ; 6.065920e+00 ; 7.642041e+00 ];

%-- Image #9:
omc_9 = [ -2.389250e+00 ; -1.670181e+00 ; 5.603389e-01 ];
Tc_9  = [ -1.501210e+02 ; -2.867581e+01 ; 1.026037e+03 ];
omc_error_9 = [ 1.137343e-02 ; 6.370102e-03 ; 1.745357e-02 ];
Tc_error_9  = [ 1.003061e+01 ; 8.616722e+00 ; 9.145618e+00 ];

%-- Image #10:
omc_10 = [ 2.585985e+00 ; 1.606967e+00 ; 2.773464e-02 ];
Tc_10  = [ 1.442403e+02 ; -1.013359e+01 ; 8.678848e+02 ];
omc_error_10 = [ 1.162921e-02 ; 5.518794e-03 ; 2.022616e-02 ];
Tc_error_10  = [ 8.611410e+00 ; 7.287043e+00 ; 8.916069e+00 ];

%-- Image #11:
omc_11 = [ 2.088548e+00 ; 2.199394e+00 ; -2.498908e-01 ];
Tc_11  = [ 1.076990e+02 ; -1.466023e+02 ; 1.295827e+03 ];
omc_error_11 = [ 1.306331e-02 ; 1.415077e-02 ; 2.784835e-02 ];
Tc_error_11  = [ 1.278630e+01 ; 1.081839e+01 ; 1.275248e+01 ];

%-- Image #12:
omc_12 = [ 2.637585e+00 ; 1.413987e+00 ; 6.107207e-01 ];
Tc_12  = [ -3.068141e+02 ; -5.659962e+01 ; 1.291005e+03 ];
omc_error_12 = [ 1.779109e-02 ; 1.019382e-02 ; 3.001560e-02 ];
Tc_error_12  = [ 1.288958e+01 ; 1.096732e+01 ; 1.427437e+01 ];

%-- Image #13:
omc_13 = [ 2.202478e+00 ; 1.773413e+00 ; 7.329377e-01 ];
Tc_13  = [ -5.364887e+02 ; -8.407617e+01 ; 1.186841e+03 ];
omc_error_13 = [ 1.560280e-02 ; 1.490595e-02 ; 2.927629e-02 ];
Tc_error_13  = [ 1.245037e+01 ; 1.043576e+01 ; 1.383175e+01 ];

%-- Image #14:
omc_14 = [ 2.214260e+00 ; 1.098970e+00 ; 7.049216e-01 ];
Tc_14  = [ -3.209856e+02 ; -7.099239e+01 ; 1.260214e+03 ];
omc_error_14 = [ 1.112109e-02 ; 6.927782e-03 ; 1.457028e-02 ];
Tc_error_14  = [ 1.266471e+01 ; 1.073047e+01 ; 1.451541e+01 ];

%-- Image #15:
omc_15 = [ 2.259050e+00 ; 1.920956e+00 ; 1.255442e-01 ];
Tc_15  = [ -2.413388e+02 ; -1.887023e+02 ; 1.621979e+03 ];
omc_error_15 = [ 2.050440e-02 ; 2.285046e-02 ; 4.532907e-02 ];
Tc_error_15  = [ 1.605895e+01 ; 1.369931e+01 ; 1.827740e+01 ];

%-- Image #16:
omc_16 = [ 1.911845e+00 ; 1.746695e+00 ; 6.280906e-01 ];
Tc_16  = [ -1.770366e+02 ; 2.739441e+01 ; 4.344343e+02 ];
omc_error_16 = [ 8.724498e-03 ; 5.430541e-03 ; 1.186675e-02 ];
Tc_error_16  = [ 4.414939e+00 ; 3.775332e+00 ; 4.758308e+00 ];

%-- Image #17:
omc_17 = [ 2.444855e+00 ; 1.632962e+00 ; -1.641743e-01 ];
Tc_17  = [ -4.975081e+01 ; 6.368565e+01 ; 5.113053e+02 ];
omc_error_17 = [ 8.125314e-03 ; 4.803703e-03 ; 1.633971e-02 ];
Tc_error_17  = [ 5.024547e+00 ; 4.291412e+00 ; 4.928097e+00 ];

%-- Image #18:
omc_18 = [ 2.222590e+00 ; 2.097836e+00 ; 4.656335e-01 ];
Tc_18  = [ -3.472877e+01 ; -1.624282e+02 ; 5.130218e+02 ];
omc_error_18 = [ 9.254362e-03 ; 7.193735e-03 ; 1.374347e-02 ];
Tc_error_18  = [ 5.129881e+00 ; 4.337413e+00 ; 5.242600e+00 ];

%-- Image #19:
omc_19 = [ 2.215139e+00 ; 2.102468e+00 ; 4.781178e-01 ];
Tc_19  = [ -2.605325e+02 ; -1.527897e+02 ; 5.056196e+02 ];
omc_error_19 = [ 7.513356e-03 ; 8.656041e-03 ; 2.017550e-02 ];
Tc_error_19  = [ 5.174994e+00 ; 4.578979e+00 ; 5.798067e+00 ];

%-- Image #20:
omc_20 = [ 2.636852e+00 ; 1.368050e+00 ; -5.653743e-02 ];
Tc_20  = [ -2.012711e+02 ; -8.830403e+01 ; 5.867933e+02 ];
omc_error_20 = [ 8.044917e-03 ; 6.557876e-03 ; 1.343606e-02 ];
Tc_error_20  = [ 5.814497e+00 ; 5.018953e+00 ; 5.932988e+00 ];

%-- Image #21:
omc_21 = [ -1.874071e+00 ; -2.302951e+00 ; 7.884622e-01 ];
Tc_21  = [ 1.361428e+02 ; -2.041983e+02 ; 7.428248e+02 ];
omc_error_21 = [ 1.199179e-02 ; 7.639189e-03 ; 1.485858e-02 ];
Tc_error_21  = [ 7.511084e+00 ; 6.128300e+00 ; 6.669721e+00 ];

%-- Image #22:
omc_22 = [ 2.174183e+00 ; 2.030065e+00 ; 3.426252e-01 ];
Tc_22  = [ -2.250496e+02 ; -2.603669e+02 ; 1.003220e+03 ];
omc_error_22 = [ 1.098994e-02 ; 1.428328e-02 ; 2.626851e-02 ];
Tc_error_22  = [ 1.012335e+01 ; 8.617943e+00 ; 1.093152e+01 ];

%-- Image #23:
omc_23 = [ -1.944781e+00 ; -2.007387e+00 ; 3.178851e-01 ];
Tc_23  = [ 1.964032e+02 ; -3.046057e+02 ; 1.136341e+03 ];
omc_error_23 = [ 1.640622e-02 ; 1.767496e-02 ; 3.234502e-02 ];
Tc_error_23  = [ 1.144288e+01 ; 9.493554e+00 ; 1.080858e+01 ];

