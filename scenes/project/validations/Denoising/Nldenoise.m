function Nldenoise(f, r, k)
    file_name = 'C:/Users/Rongxing/Desktop/ETH/CG/nori/scenes/project/validations/Denoising/cbox_path_mis';
    dat = exrread(strcat(file_name, '.exr'));
    dat_var = exrread(strcat(file_name, '_var.exr'));
    flt = zeros(size(dat));
    wgtsum = zeros(size(dat));
    box2 = fspecial("average",2*f+1); 
    dat_var = max(dat_var, convn(dat_var,box2, 'same'));

    for dx = -r:r
        for dy= -r:r
            ngb = circshift(dat,[dx,dy]);
            d2pixel = (((dat - ngb).^2) - (2*dat_var)) ./ ( eps + k^2 * (2*dat_var));
            boxf = fspecial("average",2*f+1); 
            d2patch = convn(d2pixel, boxf, 'same');
            wgt = exp(-max(0, d2patch));
            boxf1 = fspecial("average",2*f-1);
            wgt = convn(wgt, boxf1, 'same');
            flt = flt + wgt .* ngb;
            wgtsum = wgtsum + wgt;
        end
    end
    flt =flt./wgtsum;
    exrwrite(flt, strcat('cbox_path_mis', '_denoised.exr'));


end

       
